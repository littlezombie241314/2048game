#ifndef SPEEDMODEL_H
#define SPEEDMODEL_H

#include <QMainWindow>
#include <QSoundEffect>
#include "speedshowresult.h"   //竞速模式游戏成绩的文件


namespace Ui {
class SpeedModel;
}

class SpeedModel : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpeedModel(QWidget *parent = 0);
    ~SpeedModel();
    void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

    int TimerNums;                       //用来计时的变量

    int ** SpeedNums = NULL;              //创建二维数组(贴图用的主要数组)
    int ** LaterNums = NULL;                //记录贴图数组临时数据的数组

    void keyReleaseEvent(QKeyEvent *ev);   //拦截键盘输入的函数,需要对其重写

    /**1、进行初始化*/
     void InitSpeedNums();                      //开辟数组空间，并且初始化二维数组


     /**2、进行单行处理*/
     void judgeShowSpeed(int * nums);       //将数组每一行单独拿出来处理，然后在放回去


     /**3、将贴图数组的值赋给临时数组*/
     void SetSpeedNums();

     /**4、判断游戏胜负的函数*/
     void SpeedResult();

     /**5、定时系统*/
     void TimerSystem();

     /**6、维护一个音乐的指针*/
     QSoundEffect * clickMusic = new QSoundEffect; //实例化音乐对象
     QSoundEffect * EraseSound =new QSoundEffect;
     QSoundEffect * sound = new QSoundEffect;

     void SetMusicSpeed();              //音乐播放的设置

    /**7、维护一个游戏成绩界面的指针，用于界面间的切换*/
    SpeedShowResult * speedSult = NULL;

    /**8、倒计时时不可进行观看成绩和帮助文档*/
    int tempNums = 0;
    int tempNumsTwo = 0;   //倒计时声音响起时不可点返回按钮

    /**如果倒计时未完就游戏失败,那就不执行倒计时那边游戏结束的提醒*/
    bool tempTimer = true;


private:
     Ui::SpeedModel *ui;

signals:
    void SpeedBackSelect();    //返回登录界面的信号函数
};

#endif // SPEEDMODEL_H
