#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//MyButton::MyButton(QWidget *parent) :
//    QPushButton(parent)
//{


//}


MyButton::MyButton(QString path)
{
    QPixmap pix;
    bool ret = pix.load(path);   //加载图片
    if(!ret)
    {
        qDebug() << "图片加载失败" << endl;
        return;
    }

    //一、如果加载成功,首先设置图片的固定尺寸
    this->setFixedSize(pix.width(), pix.height());  //大小是传入图片的宽和高
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //二、创建图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width(), pix.height()));

}

void MyButton::downBoom()
{
    //创建动画的对象     "geometry"要记住，是一个动画特效
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置时间间隔
    animation->setDuration(200); //毫秒

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y() + 15,this->width(),this->height() ));

    //结束位置
   animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height() ));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyButton::upBoom()
{
    //创建动画的对象     "geometry"要记住，是一个动画特效
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置时间间隔
    animation->setDuration(200); //毫秒

    //起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height() ));

    //结束位置
   animation->setEndValue(QRect(this->x(),this->y() - 10,this->width(),this->height() ));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
