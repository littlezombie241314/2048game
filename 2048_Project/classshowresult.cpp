#include "classshowresult.h"
#include "ui_classshowresult.h"
#include <QFile>
#include <QSoundEffect>
#include <QPainter>

ClassShowResult::ClassShowResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassShowResult)
{
    ui->setupUi(this);
    QSoundEffect * clickMusic = new QSoundEffect;
    clickMusic->setSource(QUrl::fromLocalFile("./Du.wav"));
    clickMusic->setVolume(1);

    setWindowTitle("成绩展示");       //设置窗口标题
    setFixedSize(400,500);             //设置窗口大小
    this->setWindowIcon(QIcon(":/res/2048Icon.png"));

    ui->textEditOne->clear();

    //刷新按钮
    connect(ui->commandLinkButtonTwo, &QCommandLinkButton::clicked,[=](){
        clickMusic->play();
        ui->textEditOne->clear();
        QFile file("./GameResult.txt");
        file.open(QIODevice::ReadOnly);
        QString str = file.readAll();
        ui->textEditOne->setText(str);
        file.close();
    });

    //清空统计数据按钮
    connect(ui->commandLinkButtonThree, &QCommandLinkButton::clicked,[=](){
        clickMusic->play();
        QFile file("./GameResult.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        ui->textEditOne->clear();
        file.close();
    });

    //返回按钮
    connect(ui->commandLinkButtonOne, &QCommandLinkButton::clicked,[=](){
        clickMusic->play();
        emit this->ShowBackClass();
    });

}

ClassShowResult::~ClassShowResult()
{
    delete ui;
}

//void ClassShowResult::paintEvent(QPaintEvent *)
//{
//    //创建背景
//    QPainter painter(this);
//    QPixmap pix;
//    pix.load(":/res/PlayLevelSceneBg.png");
//    painter.drawPixmap(0,0,this->width(),this->height(),pix);
//}
