#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QWidget>
#include "classmodel.h"
#include "speedmodel.h"
#include "mybutton.h"

class SelectLevel : public QWidget
{
    Q_OBJECT
public:
    explicit SelectLevel(QWidget *parent = 0);

    ClassModel * classes = NULL;  //用于selectLevel.cpp和classmodel.cpp之间联系,比如窗口切换。

    //SpeedModel * speed = NULL;    //用于selectLevel.cpp和speedmodel.cpp之间联系,比如窗口切换。

    void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

    int temp = 0;

    MyButton * Mybtn = NULL;              //用来执行按钮的创建和弹跳动画的执行
    MyButton * MybtnTwo = NULL;              //用来执行按钮的创建和弹跳动画的执行

signals:
    void BackMainWindow();    //返回登录界面的信号函数

    //void StopMainMusic();     //关闭主界面的音乐


public slots:

};

#endif // SELECTLEVEL_H
