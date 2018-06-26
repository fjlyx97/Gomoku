#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QtNetwork>

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
    bool ifWin(int role , int x , int y);
    void resetGame();
    void qtSocket();

//重写键盘点击事件
protected:
    void mousePressEvent(QMouseEvent* );
    //void paintEvent(QPaintEvent* );


private:
    Ui::MainWindow *ui;
    //记录棋盘
    int chessboard[16][16]; //记录棋盘，横差50，纵差50，左上（38,53），右下（767,744）
    int row[16] , col[16]; //记录棋盘坐标
    bool isGameBegin; //判断游戏是否开始
    bool role;	//0黑1白
    QVector<QLabel*> labels; //记录所有下的棋子
    QTcpServer* tcpServer;	//创建服务器
    QTcpSocket* tcpSocket;  //连接服务器
};

#endif // MAINWINDOW_H
