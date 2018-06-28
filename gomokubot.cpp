#include "gomokubot.h"
#include <cstring>

GomokuBot::GomokuBot()
{
    memset(this->bookWidget,0,sizeof(this->bookWidget));
}

GomokuBot::~GomokuBot()
{

}

void GomokuBot::reset(int role)
{
    memset(this->bookWidget,0,sizeof(this->bookWidget));
    this->mrole = role;
    this->nextPutX = 0;
    this->nextPutY = 0;
}

int GomokuBot::winWidget(int putX, int putY , int role)
{
    int widget[4];
    //判断横的条件
    int mmark;
    int enemymark;

    //横行判断
    mmark = 1;
    enemymark = 0;
    for (int i = putX+1 ; i < putX+5 && i < 16 ; i++)
    {
        if (chessBoard[i][putY] == role)
        {
            mmark++;
        }
        else
        {
            enemymark++;
        }
    }
    for (int i = putX-1 ; i > 0 && i > putX-5 ; i--)
    {
        if (chessBoard[i][putY] == role)
        {
            mmark++;
        }
        else
        {
            enemymark++;
        }
    }
    widget[0] = winValue(mmark,enemymark);
    //纵行判断
    mmark = 1;
    enemymark = 0;
    for (int i = putY+1 ; i < putY+5 && i < 16 ; i++)
    {
        if (chessBoard[putX][i] == role)
        {
            mmark++;
        }
        else
        {
            enemymark++;
        }
    }
    for (int i = putY-1 ; i > 0 && i > putY-5 ; i--)
    {
        if (chessBoard[putX][i] == role)
        {
            mmark++;
        }
        else
        {
            enemymark++;
        }
    }
    widget[1] = winValue(mmark,enemymark);
}
int GomokuBot::winValue(int mmark, int enemymark)
{
    if (mmark >= 5 && enemymark == 0)
    {
        return 100000;
    }
    else if (mmark == 4 && enemymark == 0)
    {
        return 10000;
    }
    else if (mmark == 3 && enemymark == 0)
    {
        return 1000;
    }
    else if (mmark == 2 && enemymark == 0)
    {
        return 100;
    }
    else if (mmark == 1 && enemymark == 0)
    {
        return 10;
    }
    else if (mmark == 4 && enemymark == 1)
    {
        return 100;
    }
    else if (mmark == 3 && enemymark == 1)
    {
        return 100;
    }
    else
    {
        return 10;
    }
}
