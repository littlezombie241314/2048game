#include "registerface.h"
#include "ui_registerface.h"
#include <QPainter>
#include <QMessageBox>
#include <QFile>                   //文件操作的头文件
#include <QDebug>
#include <QSoundEffect>      //声音头文件
#include <QTimer>
#include <QEventLoop>        //延时用到的头文件

RegisterFace::RegisterFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterFace)
{

    QSoundEffect * clickMusic = new QSoundEffect;
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);

    ui->setupUi(this);
    setWindowTitle("注册账号");
    this->setWindowIcon(QIcon(":/res/2048Icon.png"));





    //下面这两句是让输入条中显示 “请输入....”这句话
    ui->lineEditOne->setPlaceholderText("请输入用户名");
    ui->lineEditTwo->setPlaceholderText("请输入密码");


    //下面是返回按钮
    BackButton = new MyButton(":/res/fanhui.png");   //注册按钮实例化
    BackButton->setParent(this);
    BackButton->move(QPoint(this->width() / 2 + 15,this->height() / 2 + 35));
    connect(BackButton, &QPushButton::clicked,[=](){
        clickMusic->play();
        BackButton->downBoom();                  //播放动画
        QEventLoop eventloop;                               //延时，让弹跳动画播放
        QTimer::singleShot(400, &eventloop,SLOT(quit()));
        eventloop.exec();
        QMessageBox::about(this,"提示","返回登录界面");
        emit this->RegisterBackMain();
    });

    //下面是点击注册按钮后，将检查输入条中的内容并放入文件中
    RegisterButton = new MyButton(":/res/zhuce.png");   //注册按钮实例化
    RegisterButton->setParent(this);
    RegisterButton->move(QPoint(this->width() / 2 - 120,this->height() / 2 + 35));
    connect(RegisterButton, &QPushButton::clicked,[=](){
        clickMusic->play();
        RegisterButton->downBoom();                  //播放动画
        QEventLoop eventloop;                               //延时，让弹跳动画播放
        QTimer::singleShot(400, &eventloop,SLOT(quit()));
        eventloop.exec();
        QString name = ui->lineEditOne->text();         //把条中用户名记录下来
        QString password = ui->lineEditTwo->text();   //把条中密码记录下来

        //读取内容
        QFile file("./userName.txt");  //参数就是读取文件的路径
         //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString arrayName;          //读取用户名
        QString arraytemp;           //临时把密码行读掉,以便下次arrayName可以读取用户名
        int temp = 0;                     //判断是否有重复的用户名的变量

        QTextStream in(&file);
        while(!in.atEnd())
        {
            //之所以采用此方法，不用file.readline,因为file.readline()会连换行一起读取。
            arrayName = in.readLine();        //读一行用户名，读一行密码
            arraytemp = in.readLine();
            if(name == arrayName)
            {
                  temp = 1;                                //说明有重复的用户名，则此用户名不可创建
            }
        }

        if(temp != 0)
        {
              QMessageBox::about(this,"警告","该用户已存在！");
              ui->lineEditOne->clear();       //把刚刚往用户名条里输入的数据清空
              ui->lineEditTwo->clear();       //把刚刚往密码条里输入的数据清空
        }
        else
        {
            if(name.isEmpty())
            {
                QMessageBox::about(this,"警告","用户名不可为空");
                ui->lineEditOne->clear();       //把刚刚往用户名条里输入的数据清空
                ui->lineEditTwo->clear();       //把刚刚往密码条里输入的数据清空
            }
            else if(password.isEmpty())
            {
                QMessageBox::about(this,"警告","密码不可为空");
                ui->lineEditOne->clear();       //把刚刚往用户名条里输入的数据清空
                ui->lineEditTwo->clear();       //把刚刚往密码条里输入的数据清空
            }
            else
            {
                QFile file("./userName.txt");
                file.open(QIODevice::Text |  QIODevice::WriteOnly | QIODevice::Append);
                QTextStream out(&file);
                out <<  name << endl;
                out << password << endl;
                QMessageBox::about(this,"","注册成功！");
                emit this->RegisterBackMain();     //这里也来触发一下返回的信号
            }

        }

        file.close();                                      //操作完毕后关闭文件
    });
}
RegisterFace::~RegisterFace()
{
    delete ui;
}

void RegisterFace::paintEvent(QPaintEvent *)
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
