#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QSound>         //音乐所需头文件。注意:需要包含multimedia模块才可使用
#include <QSoundEffect> //音乐头文件(适合播放短小声音)
#include <QEventLoop>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/res/2048Icon.png"));
    this->setWindowTitle("登录");

    //音乐设置
    QSound * soundMain = new QSound("./MainMusic.wav",this);
    soundMain->setLoops(-1);        //循环播放
    soundMain->play();
    QSoundEffect * clickMusic = new QSoundEffect;
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);        //设置音量大小


    //上面都是监听选择关卡返回按钮。。或者登录按钮的一些设置
//---------------------------------------------------------------------------------------------------------
    //下面是登录时，对于输入条的设置和注册时的跳转
    //lineEditOne是用户名那个条，lineEditTwo是密码那个条
    ui->lineEditOne->setPlaceholderText("请输入用户名");
    ui->lineEditTwo->setPlaceholderText("请输入密码");

    select = new SelectLevel;    //实例化对象
    MainButtonOne = new MyButton(":/res/denglu.png");   //登录按钮实例化
    MainButtonOne->setParent(this);
    MainButtonOne->move(QPoint(this->width() / 2 + 15,this->height() / 2 + 35));
    connect(MainButtonOne,&QPushButton::clicked,[=](){

        clickMusic->play();
        MainButtonOne->downBoom();                  //播放动画
        QEventLoop eventloop;                               //延时，让弹跳动画播放
        QTimer::singleShot(400, &eventloop,SLOT(quit()));
        eventloop.exec();


            //读取内容
            QFile file("./userName.txt");  //参数就是读取文件的路径
             //设置打开方式
            file.open(QIODevice::ReadOnly);
            QString arrayName;   //读取用户名
            QString arrayPassword;  //取密码
            int temp = 0;                     //判断是否有匹配的用户名的变量

            QTextStream in(&file);
            while(!in.atEnd())
            {
                //之所以采用此方法，不用file.readline,因为file.readline()会连换行一起读取。
                arrayName = in.readLine();        //读一行用户名，读一行密码
                arrayPassword = in.readLine();

                if(arrayName == ui->lineEditOne->text() && ui->lineEditOne->text() != "")   //判断用户名是否匹配
                {
                    temp = 1;         //说明有匹配的用户名
                    break;
                }
            }
            if(temp == 1)          //找到匹配的用户名,接下来判断该用户名的密码是否匹配
            {
                    if(arrayPassword == ui->lineEditTwo->text())
                    {
                        QMessageBox::about(this,"提示","登录成功");
                        this->hide();                  //登录界面隐藏
                        select->show();              //选择关卡界面启动
                    }
                    else
                    {
                        QMessageBox::about(this,"警告","用户名或密码错误");
                        ui->lineEditTwo->clear();   //把密码栏清空
                    }
            }
            else
            {
                QMessageBox::about(this,"警告","没有找到此用户信息");
            }
    });

    //监听选择关卡那边的返回按钮
    connect(select, &SelectLevel::BackMainWindow,[=](){
        select->hide();
        this->show();
        ui->lineEditTwo->clear();      //把密码栏清空
    });

    //下面是注册按钮的设置
    face = new RegisterFace;          //实例化对象
    MainButtonTwo = new MyButton(":/res/zhuce.png");   //注册按钮实例化
    MainButtonTwo->setParent(this);
    MainButtonTwo->move(QPoint(this->width() / 2 - 120,this->height() / 2 + 35));
    connect(MainButtonTwo,&QPushButton::clicked,[=](){
        clickMusic->play();
        MainButtonTwo->downBoom();                  //播放动画
        QEventLoop eventloop;                               //延时，让弹跳动画播放
        QTimer::singleShot(400, &eventloop,SLOT(quit()));
        eventloop.exec();
        if(QMessageBox::question(this,"提示","您要注册账号吗?","确定","取消") == 0)
        {
            clickMusic->play();
            this->hide();
            face->show();
        }
    });

    //监听注册页面返回的按钮
    connect(face, &RegisterFace::RegisterBackMain,[=](){
        clickMusic->play();
        face->hide();
        this->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/denglubg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/yonghuming.png");
    painter.drawPixmap(30,70,pix.width(),pix.height(),pix);
    pix.load(":/res/mima.png");
    painter.drawPixmap(48,73 + pix.height(),pix.width(),pix.height(),pix);
}
