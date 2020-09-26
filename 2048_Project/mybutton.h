#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyButton(QWidget *parent = 0);

    //因为是自定义按钮，所以重写一下构造函数
    MyButton(QString path);

    //弹跳特效
    void downBoom(); //向下跳

    void upBoom();     //向上跳

signals:

public slots:

};

#endif // MYBUTTON_H
