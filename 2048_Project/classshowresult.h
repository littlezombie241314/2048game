#ifndef CLASSSHOWRESULT_H
#define CLASSSHOWRESULT_H

#include <QWidget>

namespace Ui {
class ClassShowResult;
}

class ClassShowResult : public QWidget
{
    Q_OBJECT

public:
    explicit ClassShowResult(QWidget *parent = 0);
    ~ClassShowResult();
    //void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

private:
    Ui::ClassShowResult *ui;

signals:
    void ShowBackClass();    //返回登录界面的信号函数
};

#endif // CLASSSHOWRESULT_H
