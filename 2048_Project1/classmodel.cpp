#include "classmodel.h"
#include <QDebug>        //输出用的头文件
#include <QPainter>       //用来贴图用的头文件
#include <QMenuBar>    //菜单栏必要头文件
#include <QMessageBox> //对话框头文件,比如退出游戏时询问是否退出那个的对话框
#include <QLabel>           //标签所用的头文件
#include <QKeyEvent>     //键盘输入用到的文件
#include <QPushButton>  //先往屏幕上输出按钮，然后在按钮上贴图(按钮贴图)
#include <QPixmap>        //贴图采用QPixmap方式，所用头文件
#include <QDialog>          //对话框头文件
#include <QFile>             //用来向文件中存储游戏成绩
#include <QDateTime>    //用来获取电脑时间
#include <QSound>         //音乐所需头文件。注意:需要包含multimedia模块才可使用
#include <QCommandLinkButton>  //另一种按钮的头文件

ClassModel::ClassModel(QWidget *parent) :
    QMainWindow(parent)
{
    setSoundModel();         //设置音乐模式
    QSoundEffect * clickMusic = new QSoundEffect;
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);

    this->setWindowIcon(QIcon(":/res/2048Icon.png"));
    setWindowTitle("经典模式");       //设置窗口标题
    setFixedSize(400,500);             //设置窗口大小

    //设置第二首音乐
    QSound * soundMain = new QSound("./ClassMusic.wav",this);
    soundMain->setLoops(-1);

    QCommandLinkButton * combtn = new QCommandLinkButton("返回",this);
    combtn->setFixedSize(80,40);
    combtn->move(this->width() - 90,this->height() - 45);
    connect(combtn, &QCommandLinkButton::clicked, [=](){
        clickMusic->play();
        InitClassNums();            //因为按返回按钮，所以游戏记录重置
        emit this->EmitShow();
    });


    /**设置该窗口的菜单栏*/
    QMenuBar * menuOne = menuBar();
    setMenuBar(menuOne);
    QMenuBar * menuTwo = menuBar();
    setMenuBar(menuTwo);
    QMenuBar * menuThree = menuBar();
    setMenuBar(menuThree);
    QMenuBar * menuFour = menuBar();
    setMenuBar(menuFour);
    //上面实例化出4个菜单栏指针，下面代码开始创建对应的属性

    QMenu * AcOne = menuOne->addMenu("开始");
    QMenu * AcTwo = menuTwo->addMenu("查看");

    QMenu * Help = menuThree->addMenu("帮助");

    QAction * help = Help->addAction("帮助文档");
    QAction * actionOne = AcOne->addAction("重来");
    QAction * actionFour = AcOne->addAction("读取");
    QAction * actionTwo = AcOne->addAction("保存");
    QAction * actionThree =  AcOne->addAction("退出");
    QAction * actionfind = AcTwo->addAction("查看往届记录");

                                                 //上面的工作是对于菜单栏的设置。
//---------------------------------------------------------------------------------------------------------------
                                                 //下面对菜单栏的基本功能做一个实现

    //一、首先是退出功能
    connect(actionThree, &QAction::triggered, [=](){
        QMessageBox * mesOne = new QMessageBox(this);
        if(mesOne->question(this, "退出游戏","您确定要退出游戏吗?","再玩会","狠心退出") == 1)
        {
            clickMusic->play();
            //上面就是判断用户点的是哪个,如果返回值是1，那就是"狠心退出"按钮.
            close();     //退出游戏
        }
    });

 //---------------------------------------------------------------------------------------------------------------

    //二、'重来'的实现
    connect(actionOne,&QAction::triggered,[=](){
        clickMusic->play();
        QMessageBox * mesOne = new QMessageBox(this);
        if(mesOne->question(this, "重来","您确定要重来吗？","确定","再等等") == 0)
        {
            clickMusic->play();
            InitClassNums();     //二维数组的初始化
            update();
        }

    });

 //-----------------------------------------------------------------------------------------------------------------

    //三、‘帮助’的实现
    connect(help, &QAction::triggered,[=](){
        clickMusic->play();
        QDialog  * dia = new QDialog(this);    //模态对话框实例化对象
        dia->setWindowTitle("帮助");
        dia->resize(300,250);                         //设置窗口大小
        QLabel * lab = new QLabel;                //标签实例化，把标签放在对话框中,往标签里填文字
        lab->setParent(dia);                                   //标签放入对话框
        lab->setFixedSize(300,250);              //标签大小的设置
        lab->setFont(QFont("华文中宋",13));   //设置字体和字号

        QString str = QString("一、操作方法: 小键盘上下左右控制\n二、胜负规则: 如果出现2048则胜利\n       如果无法移动则失败\n三、如果退出游戏,则谨记菜单栏\n       保存功能\n四、菜单栏中可以实现重来,\n       保存,退出等功能");
        lab->setText(str);

        dia->exec();   //有阻塞功能,关闭对话框才能进行后面代码的执行
    });

    //四、"保存"功能的实现
    connect(actionTwo,&QAction::triggered,[=](){
        clickMusic->play();
        QFile file("./ClassData.cfg");             //经典模式的游戏数据存储
        file.open(QIODevice::ReadWrite);
        QDataStream out(&file);

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                out << ClassNums[i][j];
            }
        }
        QMessageBox::about(this,"提示","游戏数据成功保存！");

        file.close();           //存完关闭文件
    });

    //五、'读取'  功能的实现
    connect(actionFour,&QAction::triggered,[=](){
        clickMusic->play();
        QFile file("./ClassData.cfg");
        file.open(QIODevice::ReadWrite);
        QDataStream ram(&file);
        int tempNums;
        int Nums[4][4];            //临时数组用来存储读来的数据,以便判断数据是否正确
        int temp = 0;                //判断那临时数组数据的变量
        for(int i = 0; i < 4; i++)  //先把文件中的数据赋给临时数组
        {
            for(int j = 0; j < 4; j++)
            {
                ram >> tempNums;
                Nums[i][j] = tempNums;
            }
        }
        for(int i = 0; i < 4; i++)                //判断临时数组中是否有除零以外的数
        {
            for(int j = 0; j < 4; j++)
            {
                if(Nums[i][j] != 0)
                    temp++;
            }
        }
        if(temp == 0)                              //说明文件有数据,所以可以成功读取
        {
            QMessageBox::about(this,"警告","无存档数据访问");
            return;
        }
        else
        {
            for(int i = 0; i < 4; i++)                 //把临时数组中的值赋给贴图数组
            {
                for(int j = 0; j < 4; j++)
                {
                    ClassNums[i][j] = Nums[i][j];
                }
            }

            QMessageBox::about(this,"提示","读取成功");
            update();
        }
    });

    //查看游戏成绩(因为要向文件中显示游戏成绩，那我就专门在弄一个显示窗口)
    ScoreShow = new ClassShowResult;
    connect(actionfind,&QAction::triggered, [=](){
        clickMusic->play();
        this->hide();          //本窗口隐藏
        ScoreShow->show();      //展示成绩窗口显示
    });

    //监听查看游戏成绩窗口返回的信号
    connect(ScoreShow, &ClassShowResult::ShowBackClass,[=](){
        ScoreShow->hide();
        this->show();
    });

                                                   //上面是菜单栏功能的实现
//---------------------------------------------------------------- -------------------------------------------------


    InitClassNums();     //二维数组的初始化


}

//进行贴图
void ClassModel::paintEvent(QPaintEvent *)
{
    update();     //先刷新一下
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    for(int i = 0; i < 4; i++)       //贴图
    {
        for(int j = 0; j < 4; j++)
        {
             QString str = QString(":/res/%1.png").arg(QString::number(ClassNums[i][j]));
             pix.load(str);
             painter.drawPixmap(60 + j * 70,130 + i * 70,pix.width(),pix.height(),pix);
        }
    }
}

void ClassModel::setSoundModel()
{
    //设置消除音效的模式
    EraseSound = new QSoundEffect;
    EraseSound->setSource(QUrl::fromLocalFile("./Eliminate.wav"));
    EraseSound->setLoopCount(1);  //播放一次
    EraseSound->setVolume(1);       //设置音量
}

//初始化二维数组
void ClassModel::InitClassNums()
{
    /**贴图数组初始化*/
    ClassNums = new int *[4];          //动态声明二维数组，开辟列
    for(int i = 0; i < 4; i++)                 //二维数组的行进行开辟
    {
        ClassNums[i] = new int[4];      //开辟了行
    }
    /**临时数组初始化*/
    LaterNums = new int *[4];          //动态声明二维数组，开辟列
    for(int i = 0; i < 4; i++)                 //二维数组的行进行开辟
    {
        LaterNums[i] = new int[4];      //开辟了行
    }



    //接下来进行初始化数据,该游戏中默认没数字的地方存储0；
    //初始时先随机两个位置为2，剩下的全部为0

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ClassNums[i][j] = 0;
        }
    }

    int temp = 0;   //判断初始的两个2是否随机产生成功
    while(temp <= 1)
    {
        int x = qrand() % 4;
        int y = qrand() % 4;
        if(ClassNums[x][y] == 0)
        {
           ClassNums[x][y] = 2;
            temp++;
        }
    }
}

//进行单行处理
void ClassModel::judgeShowUP(int * nums)
{

    for(int i = 0; i < 4; i++)                     //通过遍历，来进行数值的移动
    {
        for(int j = i; j > 0; j--)
        {
            if(nums[j - 1] == 0)
            {
                nums[j - 1] = nums[j];
                nums[j] = 0;
            }
            else if(nums[j - 1] == nums[j])
            {
                EraseSound->play();
                nums[j - 1] += nums[j];
                nums[j] = 0;
                break;
            }
        }
    }
}

/**3、将贴图数组的值赋给临时数组*/
void ClassModel::SetTempNums()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            LaterNums[i][j] = ClassNums[i][j];     //赋值
        }
    }
}

//判断游戏胜负
void ClassModel::GameResult()
{
    for(int i = 0; i < 4; i++)              //通过for循环遍历，判断数组中是否有2048
    {
        for(int j = 0; j < 4; j++)
        {
            if(ClassNums[i][j] == 2048)
            {
                if(QMessageBox::question(this,"提示","您要保存记录吗？","保存","取消") == 1)
                {
                    QMessageBox::about(this,"游戏结果","恭喜您获胜了,游戏记录已保存");
                    InitClassNums();                    //初始化
                    emit this->EmitShow();
                }
                else
                {
                    int MaxNums = ClassNums[0][0];   //存储贴图数组中的最大值
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(MaxNums < ClassNums[i][j])
                            {
                                MaxNums = ClassNums[i][j];
                            }
                        }
                    }

                    //下面开始存储
                    QDateTime * data = new QDateTime(QDateTime::currentDateTime());
                    QString str = data->toString("yyyy-MM-dd  hh:mm:ss ");
                    QFile file("./GameResult.txt");
                    file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);

                    QString  s = QString("分数: %1     时间：%2 \n").arg(MaxNums).arg(str);
                    file.write(s.toUtf8());
                    file.close();
                    InitClassNums();                 //对数组进行一次初始化
                    update();
                }
            }
        }
    }

    int tempTest = 0;                 //判断是否还有能消的块，没有则游戏失败
    for(int i = 0; i < 4; i++)          //遍历整个数组，判断每个元素的前后左右
    {
        for(int j = 0; j < 4; j++)
        {
            if(i - 1 >= 0)   //如果此位置存在
            {
                if(ClassNums[i][j] == ClassNums[i - 1][j])
                    tempTest = 1;
            }
            if(i + 1 <= 3)   //如果此位置存在
            {
                if(ClassNums[i][j] == ClassNums[i + 1][j])
                    tempTest = 1;
            }
            if(j - 1 >= 0)   //如果此位置存在
            {
                if(ClassNums[i][j] == ClassNums[i][j - 1])
                    tempTest = 1;
            }
            if(j + 1 <= 3)   //如果此位置存在
            {
                if(ClassNums[i][j] == ClassNums[i][j + 1])
                    tempTest = 1;
            }
        }
    }
    if(tempTest == 0)                  //此情况说明目前没有可以相消的块了
    {
        for(int i = 0; i < 4; i++)       //没有相消的块，最后判断有没有空余的位置,如果没有，那就输了
        {
            for(int j = 0; j < 4; j++)
            {
                if(ClassNums[i][j] == 0)
                {
                    return;
                }
            }
        }
        QMessageBox::about(this,"游戏结果","游戏失败");
        int MaxNums = ClassNums[0][0];   //存储贴图数组中的最大值
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(MaxNums < ClassNums[i][j])
                {
                    MaxNums = ClassNums[i][j];
                }
            }
        }
        QString  strTemp = QString("您的分数为 %1").arg(MaxNums);
        QMessageBox::about(this,"提示",strTemp);
        if(QMessageBox::question(this,"提示","您要保存记录吗？","保存","取消") == 1)
        {
            InitClassNums();
            emit this->EmitShow();
            //update();
        }
        else
        {
            //下面开始存储
            QDateTime * data = new QDateTime(QDateTime::currentDateTime());
            QString str = data->toString("yyyy-MM-dd  hh:mm:ss ");
            QFile file("./GameResult.txt");
            file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);
            QString  s = QString("分数: %1     时间：%2 \n").arg(MaxNums).arg(str);
            file.write(s.toUtf8());
            file.close();
            InitClassNums();                 //对数组进行一次初始化
            emit this->EmitShow();
            //update();
        }
        return;
    }
}

//每次操作后产生随机块
void RandNums(int *nums[4], int * numsLater[4])
{
    //产生随机块的条件是数组有移动才行，所以先判断原数组和改变后的数组是否不同
    int temp = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(nums[i][j] != numsLater[i][j])
            {
                temp = 1;
            }
        }
    }

    if(temp != 0)                    //不同，那就产生随机块
    {
        while(true)
        {
            int x,y;
            x = qrand() % 4;
            y = qrand() % 4;
            if(nums[x][y] == 0)
            {
                nums[x][y] = 2;
                break;
            }
        }
    }
}


//通过按键的判断来进行贴图,贴图的依据是数组里的值
void ClassModel::keyReleaseEvent(QKeyEvent *ev)
{

    switch(ev->key()){
    case Qt::Key_Up:
                    GameResult();
                    SetTempNums();    //把贴图数组的值记录下来
                    int nums[4];                     //临时数组,存放一行数据
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                           nums[j] = ClassNums[j][i];
                        }
                        judgeShowUP(nums);

                        for(int K = 0; K < 4; K++)
                        {
                            ClassNums[K][i] = nums[K];
                        }
                    }
                    RandNums(ClassNums,LaterNums);
                    //上面两个函数的意思是：先记录下按键按下后贴图数组的值，然后RandNums中判断
                    //有没有位置可以产生随机块，如果有，那就产生随机块。


        //update();                 //刷新
        break;
    case Qt::Key_Down:

                   GameResult();
                   SetTempNums();    //把贴图数组的值记录下来
                   for(int i = 3; i >= 0; i--)
                   {
                       for(int j = 3; j >= 0; j--)
                       {
                          nums[3 - j] = ClassNums[j][i];
                       }
                       judgeShowUP(nums);

                       for(int K = 0; K < 4; K++)
                       {
                           ClassNums[3 - K][i] = nums[K];
                       }
                   }
                   RandNums(ClassNums,LaterNums);
                   //update();                 //刷新
                   break;
    case Qt::Key_Left:
                    GameResult();
                    SetTempNums();    //把贴图数组的值记录下来
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                           nums[j] = ClassNums[i][j];
                        }
                        judgeShowUP(nums);

                        for(int K = 0; K < 4; K++)
                        {
                            ClassNums[i][K] = nums[K];
                        }
                    }

                    RandNums(ClassNums,LaterNums);
                    //update();                 //刷新
                    break;
    case Qt::Key_Right:
                    GameResult();
                    SetTempNums();    //把贴图数组的值记录下来SetTempNums();
                    for(int i = 3; i >= 0; i--)
                    {
                        for(int j = 3; j >= 0; j--)
                        {
                           nums[3 - j] = ClassNums[i][j];
                        }
                        judgeShowUP(nums);

                        for(int K = 0; K < 4; K++)
                        {
                            ClassNums[i][3 - K] = nums[K];
                        }
                    }

                    RandNums(ClassNums,LaterNums);
                    //update();                 //刷新
                    break;

    default:    //其他按键退出函数
        return;
    }
}

ClassModel::~ClassModel()
{
    for(int i = 0; i < 4; i++)
        delete[] ClassNums[i];
    delete[] ClassNums;
}
