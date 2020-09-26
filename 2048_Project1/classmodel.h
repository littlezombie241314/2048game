#ifndef CLASSMODEL_H
#define CLASSMODEL_H

#include <QMainWindow>
#include "classshowresult.h"
#include <QSoundEffect>

class ClassModel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClassModel(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);      //想要贴图,就要重写此函数

    int ** ClassNums = NULL;                  //创建二维数组(贴图用的主要数组)
    int ** LaterNums = NULL;                   //记录贴图数组临时数据的数组

    int MusicTemp = 0;                                  //临时判断播放哪个音乐的变量

    QSoundEffect * EraseSound = NULL;

    void setSoundModel();                          //设置音乐的模式

    void keyReleaseEvent(QKeyEvent *ev);   //拦截键盘输入的函数,需要对其重写

    ClassShowResult * ScoreShow = NULL;          //维护一个展示游戏成绩的指针



    ~ClassModel();           //因为用到了二维数组，那就写析构函数进行析构

//------------------------------------------------------------------------------------------------------------------

    /**1、进行初始化*/
     void InitClassNums();                      //开辟数组空间，并且初始化二维数组


     /**2、进行单行处理*/
     void judgeShowUP(int * nums);       //将数组每一行单独拿出来处理，然后在放回去


     /**3、将贴图数组的值赋给临时数组*/
     void SetTempNums();

     /**4、判断游戏胜负的函数*/
     void GameResult();



signals:

     void EmitShow();                //用来从经典模式返回到选择关卡界面的信号


public slots:

};

#endif // CLASSMODEL_H
