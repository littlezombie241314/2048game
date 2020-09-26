#ifndef SPEEDSHOWRESULT_H
#define SPEEDSHOWRESULT_H

#include <QMainWindow>

namespace Ui {
class SpeedShowResult;
}

class SpeedShowResult : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpeedShowResult(QWidget *parent = 0);
    ~SpeedShowResult();

private:
    Ui::SpeedShowResult *ui;

signals:
    void ResultBackSpeed();    //返回竞速模式界面的信号函数
};

#endif // SPEEDSHOWRESULT_H
