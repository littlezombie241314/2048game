#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "classmodel.h"
#include "selectlevel.h"
#include "registerface.h"
#include "mybutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

    SelectLevel * select = NULL;     //用于和关卡选择界面切换

    RegisterFace * face = NULL;      //登录界面和主界面切换用

    ClassModel * classMusic = NULL;  //用来监听是否有切换音乐

    MyButton * MainButtonOne = NULL;       //自定义(登录)按钮
    MyButton * MainButtonTwo = NULL;       //自定义(注册)按钮


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
