#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void chessboardInit();
    void singerGame();

//重写键盘点击事件
protected:
    void mousePressEvent(QMouseEvent* );
    //void paintEvent(QPaintEvent* );


private:
    Ui::MainWindow *ui;
    //记录棋盘
    int chessboard[16][16]; //记录棋盘，横差50，纵差40，左上（117,120），右下（790,690）
    int row[16] , col[16]; //记录棋盘坐标
    bool isGameBegin; //判断游戏是否开始
    bool role;	//0黑1白
};

#endif // MAINWINDOW_H
