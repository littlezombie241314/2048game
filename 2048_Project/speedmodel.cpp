#include "speedmodel.h"
#include "ui_speedmodel.h"
#include <QDebug>        //输出用的头文件
#include <QPainter>       //用来贴图用的头文件
#include <QMenuBar>    //菜单栏必要头文件
#include <QMessageBox> //对话框头文件,比如退出游戏是询问是否退出那个的对话框
#include <QLabel>           //标签所用的头文件
#include <QKeyEvent>     //键盘输入用到的文件
#include <QPushButton>  //先往屏幕上输出按钮，然后在按钮上贴图(按钮贴图)
#include <QPixmap>        //贴图采用QPixmap方式，所用头文件
#include <QDialog>        //对话框头文件
#include <QFile>             //用来向文件中存储游戏成绩
#include <QDateTime>    //用来获取电脑时间
#include <QTimer>          //计数器头文件
#include <QFont>             //设置标签的字体
#include <QPalette>          //设置字体的颜色
#include <QSoundEffect>
#include <QEventLoop>      //延时所需函数


SpeedModel::SpeedModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpeedModel)
{
    ui->setupUi(this);

    this->setWindowTitle("竞速模式");       //设置窗口标题
    this->setFixedSize(400,500);             //设置窗口大小
    this->setWindowIcon(QIcon(":/res/2048Icon.png"));


    SetMusicSpeed();          //设置音乐
    TimerSystem();             //计时系统函数的调用

    //一、首先是退出功能
    connect(ui->menuOne, &QAction::triggered, [=](){

        if(QMessageBox::question(this, "退出游戏","您确定要退出游戏吗?","再玩会","狠心退出") == 1)
        {
            clickMusic->play();
            //上面就是判断用户点的是哪个,如果返回值是1，那就是"狠心退出"按钮.
            close();     //退出游戏
        }
    });


    //二、查看游戏成绩
    connect(ui->menuTwo, &QAction::triggered, [=](){

        if(tempNums == 0)
        {
            speedSult = new SpeedShowResult;            //实例化
            this->close();
            speedSult->show();
            connect(speedSult, &SpeedShowResult::ResultBackSpeed,[=](){
                speedSult->hide();
                this->show();
            });
        }
        else
            QMessageBox::about(this,"提示","计时未开时才可查看！");
    });


    //三、‘帮助’的实现
    connect(ui->actionHelp, &QAction::triggered,[=](){

        if(tempNums == 0)
        {
            QDialog  * dia = new QDialog(this);    //模态对话框实例化对象
            dia->setWindowTitle("帮助");
            dia->resize(300,250);                         //设置窗口大小
            QLabel * lab = new QLabel;                //标签实例化，把标签放在对话框中,往标签里填文字
            lab->setParent(dia);                                   //标签放入对话框
            lab->setFixedSize(300,250);              //标签大小的设置
            lab->setFont(QFont("华文中宋",13));   //设置字体和字号

            QString str = QString("一、操作方法: 小键盘上下左右控制\n二、胜负规则: 如果出现2048则胜利\n       如果无法移动或时间不足\n       则判定失败\n");
            lab->setText(str);

            dia->exec();   //有阻塞功能,关闭对话框才能进行后面代码的执行
        }
        else
            QMessageBox::about(this,"提示","计时未开时才可查看！");
    });
}

void SpeedModel::paintEvent(QPaintEvent *)
{
    update();
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);    

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            QString str = QString(":/res/%1.png").arg(QString::number(SpeedNums[i][j]));
             pix.load(str);
             painter.drawPixmap(60 + j * 70,150 + i * 70,pix.width(),pix.height(),pix);
         }
    }

}

//初始化二维数组
void SpeedModel::InitSpeedNums()
{
    /**贴图数组初始化*/
    SpeedNums = new int *[4];          //动态声明二维数组，开辟列
    for(int i = 0; i < 4; i++)                 //二维数组的行进行开辟
    {
        SpeedNums[i] = new int[4];      //开辟了行
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
            SpeedNums[i][j] = 0;
        }
    }

    int temp = 0;   //判断初始的两个2是否随机产生成功
    while(temp <= 1)
    {
        int x = qrand() % 4;
        int y = qrand() % 4;
        if(SpeedNums[x][y] == 0)
        {
           SpeedNums[x][y] = 2;
            temp++;
        }
    }
}

//进行单行处理
void SpeedModel::judgeShowSpeed(int * nums)
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
void SpeedModel::SetSpeedNums()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            LaterNums[i][j] = SpeedNums[i][j];     //赋值
        }
    }
}

//判断游戏胜负
void SpeedModel::SpeedResult()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(SpeedNums[i][j] == 2048)
            {
                tempTimer = false;
                if(QMessageBox::question(this,"提示","您要保存记录吗？","保存","取消") == 1)
                {
                    clickMusic->play();
                    QMessageBox::about(this,"游戏结果","恭喜您获胜了,游戏记录已保存");
                    InitSpeedNums();
                    emit this->SpeedBackSelect();
                }
                else
                {
                    int MaxNums = SpeedNums[0][0];   //存储贴图数组中的最大值
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(MaxNums < SpeedNums[i][j])
                            {
                                MaxNums = SpeedNums[i][j];
                            }
                        }
                    }

                    //下面开始存储
                    QDateTime * data = new QDateTime(QDateTime::currentDateTime());
                    QString str = data->toString("yyyy-MM-dd  hh:mm:ss ");
                    QFile file("./SpeedResult.txt");
                    file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);

                    QString  s = QString("分数: %1     时间：%2 \n").arg(MaxNums).arg(str);
                    file.write(s.toUtf8());
                    file.close();
                    InitSpeedNums();                 //对数组进行一次初始化
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
                if(SpeedNums[i][j] == SpeedNums[i - 1][j])
                    tempTest = 1;
            }
            if(i + 1 <= 3)   //如果此位置存在
            {
                if(SpeedNums[i][j] == SpeedNums[i + 1][j])
                    tempTest = 1;
            }
            if(j - 1 >= 0)   //如果此位置存在
            {
                if(SpeedNums[i][j] == SpeedNums[i][j - 1])
                    tempTest = 1;
            }
            if(j + 1 <= 3)   //如果此位置存在
            {
                if(SpeedNums[i][j] == SpeedNums[i][j + 1])
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
                if(SpeedNums[i][j] == 0)
                {
                    return;
                }
            }
        }
        int MaxNums = SpeedNums[0][0];   //存储贴图数组中的最大值
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(MaxNums < SpeedNums[i][j])
                {
                    MaxNums = SpeedNums[i][j];
                }
            }
        }

        tempTimer = false;         //让定时器不在工作
        QMessageBox::about(this,"游戏结果","游戏失败");
        QString  strTemp = QString("您的分数为 %1").arg(MaxNums);
        QMessageBox::about(this,"提示",strTemp);
        if(QMessageBox::question(this,"提示","您要保存记录吗？","保存","取消") == 1)
        {
            clickMusic->play();
            InitSpeedNums();
            //update();
            emit this->SpeedBackSelect();
        }
        else
        {

            //下面开始存储
            QDateTime * data = new QDateTime(QDateTime::currentDateTime());
            QString str = data->toString("yyyy-MM-dd  hh:mm:ss ");
            QFile file("./SpeedResult.txt");
            file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);

            QString  s = QString("分数: %1     时间：%2 \n").arg(MaxNums).arg(str);
            file.write(s.toUtf8());
            file.close();
            InitSpeedNums();                 //对数组进行一次初始化
            //update();
            emit this->SpeedBackSelect();
        }
        return;
    }
}

void SpeedModel::TimerSystem()
{
    setWindowTitle("竞速模式");
    setFixedSize(400,500);

    ui->labelOne->move(QPoint(150,30));

    InitSpeedNums();    //数组初始化

    //设置字体和颜色
    QFont font;
    font.setPointSize(72);
    ui->labelOne->setFont(font);
    QPalette pa;
    pa.setColor(QPalette::WindowText , Qt::yellow);
    ui->labelOne->setPalette(pa);

    TimerNums = 20;         //设定倒计时时间
    //触发定时器
    QTimer * time = new QTimer(this);

    QPushButton * btn = new QPushButton(this);
    QString str = QString("20秒倒计时");
    btn->setPalette(QPalette(Qt::blue));
    btn->setFont(QFont(str,30));
    btn->setText(str);

    btn->setFixedSize(280,280);
    btn->move(QPoint(60,150));
    connect(btn, &QPushButton::clicked,[=](){
        tempNumsTwo = 1;         //通过这个变量的值可以看出音乐播放完没
        sound->play();
        btn->close();
        tempNums = 1;
        QEventLoop eventloop;
        QTimer::singleShot(3500, &eventloop,SLOT(quit()));            //延时
        eventloop.exec();
        time->start(1000);   //每隔1秒会发一个信号出来
        QTimer::singleShot(1000, &eventloop,SLOT(quit()));
        eventloop.exec();
        tempNumsTwo = 2;
        connect(time, &QTimer::timeout,[=](){
            if(tempTimer == false)
            {
                time->stop();
            }
            else
            {

                ui->labelOne->setText(QString::number(TimerNums--));
                if(TimerNums == -1)
                {
                    time->stop();

                    QMessageBox::about(this,"提示","很遗憾,时间到了！");
                    int MaxNums = SpeedNums[0][0];   //存储贴图数组中的最大值
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(MaxNums < SpeedNums[i][j])
                            {
                                MaxNums = SpeedNums[i][j];
                            }
                        }
                    }
                    QString  strTemp = QString("您的分数为 %1").arg(MaxNums);
                    QMessageBox::about(this,"提示",strTemp);
                    if(QMessageBox::question(this,"提示","您要保存记录吗?","保存","取消") == 0)
                    {
                        clickMusic->play();
                        int MaxNums = SpeedNums[0][0];   //存储贴图数组中的最大值
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                if(MaxNums < SpeedNums[i][j])
                                {
                                    MaxNums = SpeedNums[i][j];
                                }
                            }
                        }
                        //下面开始存储
                        QDateTime * data = new QDateTime(QDateTime::currentDateTime());
                        QString str = data->toString("yyyy-MM-dd  hh:mm:ss ");
                        QFile file("./SpeedResult.txt");
                        file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);

                        QString  s = QString("分数: %1     时间：%2 \n").arg(MaxNums).arg(str);
                        file.write(s.toUtf8());
                        file.close();
                        QMessageBox::about(this,"提示","保存成功！");
                        InitSpeedNums();
                        //update();
                        emit this->SpeedBackSelect();
                    }
                    else
                    {
                        InitSpeedNums();                  //重新初始化一下数组
                        //update();                                //更新一下画面
                        emit this->SpeedBackSelect();
                    }
                }

            }

       });

 });

    //返回按钮
connect(ui->commandLinkButtonOne, &QCommandLinkButton::clicked, [=](){
    if(tempNumsTwo == 0 || tempNumsTwo == 2)
    {
        clickMusic->play();
        emit this->SpeedBackSelect();   //返回信号
    }
});
}

void SpeedModel::SetMusicSpeed()
{
    //音乐素材实例化和初始设置
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);
    EraseSound->setSource(QUrl::fromLocalFile("./Eliminate.wav"));
    EraseSound->setLoopCount(1);  //播放一次
    EraseSound->setVolume(1);       //设置音量
    sound->setSource(QUrl::fromLocalFile("./timer.wav"));
    sound->setVolume(1);
}

//每次操作后产生随机块
void RandNumsTwo(int *nums[4], int * numsLater[4])
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
            x = qrand() % 4;                 //产生随机数
            y = qrand() % 4;
            if(nums[x][y] == 0)
            {
                nums[x][y] = 2;               //随机产生一个2
                break;
            }
        }
    }
}


//通过按键的判断来进行贴图,贴图的依据是数组里的值
void SpeedModel::keyReleaseEvent(QKeyEvent *ev)
{
    if(tempNumsTwo != 0 && tempNumsTwo != 1)
    {
        switch(ev->key()){
        case Qt::Key_Up:
                        SpeedResult();
                        SetSpeedNums();                  //把贴图数组的值记录下来
                        int nums[4];                         //临时数组,存放一行数据
                        for(int i = 0; i < 4; i++)            //使用循环来进行判断
                        {
                            for(int j = 0; j < 4; j++)
                            {
                               nums[j] = SpeedNums[j][i];
                            }
                            judgeShowSpeed(nums);    //进行单行判断

                            for(int K = 0; K < 4; K++)
                            {
                                SpeedNums[K][i] = nums[K];
                            }
                        }
                        RandNumsTwo(SpeedNums,LaterNums);  //产生随机数
                        //上面两个函数的意思是：先记录下按键按下后贴图数组的值，然后RandNums中判断
                        //有没有位置可以产生随机块，如果有，那就产生随机块。


           //update();                 //刷新
            break;
        case Qt::Key_Down:

                       SpeedResult();
                       SetSpeedNums();    //把贴图数组的值记录下来
                       for(int i = 3; i >= 0; i--)
                       {
                           for(int j = 3; j >= 0; j--)
                           {
                              nums[3 - j] = SpeedNums[j][i];
                           }
                           judgeShowSpeed(nums);               //单行进行判断

                           for(int K = 0; K < 4; K++)
                           {
                               SpeedNums[3 - K][i] = nums[K];
                           }
                       }
                       RandNumsTwo(SpeedNums,LaterNums);
                       //update();                 //刷新
                       break;
        case Qt::Key_Left:
                        SpeedResult();
                        SetSpeedNums();    //把贴图数组的值记录下来
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                               nums[j] = SpeedNums[i][j];
                            }
                            judgeShowSpeed(nums);

                            for(int K = 0; K < 4; K++)
                            {
                                SpeedNums[i][K] = nums[K];
                            }
                        }

                        RandNumsTwo(SpeedNums,LaterNums);
                        //update();                 //刷新
                        break;
        case Qt::Key_Right:
                        SpeedResult();
                        SetSpeedNums();    //把贴图数组的值记录下来SetTempNums();
                        for(int i = 3; i >= 0; i--)
                        {
                            for(int j = 3; j >= 0; j--)
                            {
                               nums[3 - j] = SpeedNums[i][j];
                            }
                            judgeShowSpeed(nums);

                            for(int K = 0; K < 4; K++)
                            {
                                SpeedNums[i][3 - K] = nums[K];
                            }
                        }

                        RandNumsTwo(SpeedNums,LaterNums);
                        //update();                 //刷新
                        break;

        default:    //其他按键退出函数
            return;
        }
    }


}
SpeedModel::~SpeedModel()
{
    delete ui;
}


