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
    //初始化棋盘
    void chessboardInit();
    //本地对战
    void singerGame();
    //判断是否胜利
    bool ifWin(int role , int x , int y);
    //游戏还原
    void resetGame();
    //多人游戏
    void qtSocket();
    void acceptConnectSignal(bool misTcpConnect);
    void sendInitStatus();
    //游戏绘制
    void runGame(int putX , int putY);

//重写键盘点击事件
protected:
    void mousePressEvent(QMouseEvent* );

signals:
    void initStatus();


private:
    Ui::MainWindow *ui;
    //记录棋盘
    int chessboard[16][16]; //记录棋盘，横差50，纵差50，左上（38,53），右下（767,744）
    int row[16] , col[16]; //记录棋盘坐标
    //游戏逻辑
    bool isGameBegin; //判断游戏是否开始
    bool role;	//0黑1白
    QVector<QLabel*> labels; //记录所有下的棋子
    //服务器连接
    QTcpServer* tcpServer;	//创建服务器
    QTcpSocket* tcpSocket;  //连接服务器
    bool isTcpConnect;		//判断是否连接成功
    bool isTurn;
};

#endif // MAINWINDOW_H
