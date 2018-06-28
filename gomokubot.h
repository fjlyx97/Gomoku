#ifndef GOMOKUBOT_H
#define GOMOKUBOT_H
#include <QObject>

class GomokuBot : public QObject
{
    Q_OBJECT	//包含信号槽的宏
signals:
    void sendPutChess(int putX , int putY);
public:
    GomokuBot(int role);
    ~GomokuBot();
    void reset();		//恢复棋盘权重
    void putChess(int putX , int putY);			//接受信号获得棋盘落点.
    int winWidget(int putX,int putY , int role);	//计算可以获胜的权重
    int winValue(int mmark , int enemymark);	//返回五子棋判断得分
    /*
     * 成五，100000	死四, 1000
     * 活四, 10000	死三 100
     * 活三 1000		死二 10
     * 活二 100
     * 活一 10
     */


private:
    int bookWidget[16][16]; 	//储存当下可以获胜的权重
    int chessBoard[16][16];		//储层棋盘的所有落子
    int mrole;
    int protectWidgetMax;
    int attackWidgetMax;
    // 下一步最好的点
    int nextPutX;
    int nextPutY;
};

#endif // GOMOKUBOT_H
