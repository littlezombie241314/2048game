#include "selectlevel.h"
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QSoundEffect>
#include <QSound>
#include <QCommandLinkButton>
#include <QTimer>
#include <QEventLoop>

SelectLevel::SelectLevel(QWidget *parent) :
    QWidget(parent)
{

    //声音资源的实例化和设置
    QSoundEffect * clickMusic = new QSoundEffect;
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);

    this->setWindowIcon(QIcon(":/res/2048Icon.png"));
    setWindowTitle("关卡选择");
    setFixedSize(400,500);

    //经典模式按钮
    Mybtn = new MyButton(":/res/jingdianmoshi.png");
    Mybtn->setParent(this);
    Mybtn->move(QPoint((this->width() - 230) / 2,(this->height() - 50) / 2 - 90));

    //竞速模式按钮
    MybtnTwo = new MyButton(":/res/jingsumoshi.png");
    MybtnTwo->setParent(this);
    MybtnTwo->move(QPoint((this->width() - 230) / 2,(this->height() - 50) / 2 + 50));

    QCommandLinkButton * combtn = new QCommandLinkButton("登出",this);
    combtn->setFixedSize(80,40);
    combtn->move(this->width() - 90,this->height() - 45);
    connect(combtn, &QCommandLinkButton::clicked, [=](){
        clickMusic->play();
        emit this->BackMainWindow();
    });

    //下面根据用户的选择进行界面连接
    //如果选的是经典模式，那就连接classModel那个文件
    classes = new ClassModel;
    connect(Mybtn, &MyButton::clicked, [=](){
        Mybtn->downBoom();
        clickMusic->play();
        QEventLoop eventloop;                       //延时，让弹跳动画播放
        QTimer::singleShot(600, &eventloop,SLOT(quit()));
        eventloop.exec();
        this->hide();
        classes->show();
    });

    //连接竞速模式
    connect(MybtnTwo, &QPushButton::clicked, [=](){
        MybtnTwo->downBoom();
        //实例化竞速模式窗口，并且进行展示
        clickMusic->play();                                       //音乐播放
        QEventLoop eventloop;                               //延时，让弹跳动画播放
        QTimer::singleShot(600, &eventloop,SLOT(quit()));
        eventloop.exec();
        SpeedModel * speed = new SpeedModel;     //实例化对象
        this->hide();
        speed->show();

        //监听竞速模式的返回按钮
        connect(speed,&SpeedModel::SpeedBackSelect,[=](){
             delete speed;
             this->show();
        });
    });

    //监听经典模式返回的信号
    connect(classes,&ClassModel::EmitShow,[=](){
         classes->hide();
         this->show();
    });

}
//进行贴图
void SelectLevel::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
