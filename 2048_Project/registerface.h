#ifndef REGISTERFACE_H
#define REGISTERFACE_H

#include <QWidget>
#include "mybutton.h"

namespace Ui {
class RegisterFace;
}

class RegisterFace : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterFace(QWidget *parent = 0);
    ~RegisterFace();

    void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

    MyButton * RegisterButton = NULL;  //注册界面内的(注册)按钮
    MyButton * BackButton = NULL;       //注册页面的(返回)按钮

signals:
    void RegisterBackMain();    //返回登录界面的信号函数

private:
    Ui::RegisterFace *ui;
};

#endif // REGISTERFACE_H
