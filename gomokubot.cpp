#include "gomokubot.h"
#include <cstring>
#include <QDebug>

GomokuBot::GomokuBot(int role)
{
    memset(this->bookWidget,0,sizeof(this->bookWidget));
    memset(this->chessBoard,-1,sizeof(this->chessBoard));
    memset(this->bookChess,0,sizeof(this->bookChess));
    this->mrole = role;
}

GomokuBot::~GomokuBot()
{

}

void GomokuBot::reset()
{
    memset(this->bookWidget,0,sizeof(this->bookWidget));
    this->nextPutX = 0;
    this->nextPutY = 0;
}

int GomokuBot::winWidget(int putX, int putY , int role)
{
    int widget[4] = {0};
    //判断横的条件
    int mmark;
    int enemymark;

    //横行判断
    mmark = 0;
    enemymark = 0;
    int flag = 0;
    for (int i = putX+1 ; i < putX+5 && i < 16 ; i++)
    {
        if (flag == 1)
            break;
        if (chessBoard[i][putY] == role)
        {
            mmark++;
        }
        else if (chessBoard[i][putY] == !role && chessBoard[i][putY] != -1)
        {
            flag = 1;
            enemymark++;
        }
        else
        {
            break;
        }
    }
    flag = 0;
    for (int i = putX-1 ; i > 0 && i > putX-5 ; i--)
    {
        if (flag == 1)
            break;
        if (chessBoard[i][putY] == role)
        {
            mmark++;
        }
        else if (chessBoard[i][putY] == !role && chessBoard[i][putY] != -1)
        {
            flag = 1;
            enemymark++;
        }
        else
        {
            break;
        }
    }
    widget[0] = winValue(mmark,enemymark);
    //纵行判断
    mmark = 0;
    enemymark = 0;
    flag = 0;
    for (int i = putY+1 ; i < putY+5 && i < 16 ; i++)
    {
        if (flag == 1)
            break;
        if (chessBoard[putX][i] == role)
        {
            mmark++;
        }
        else if(chessBoard[putX][i] == !role && chessBoard[putX][i] != -1)
        {
            flag = 1;
            enemymark++;
        }
        else
        {
            break;
        }
    }
    flag = 0;
    for (int i = putY-1 ; i > 0 && i > putY-5 ; i--)
    {
        if (flag == 1)
            break;
        if (chessBoard[putX][i] == role)
        {
            mmark++;
        }
        else if(chessBoard[putX][i] == !role && chessBoard[putX][i] != -1)
        {
            flag = 1;
            enemymark++;
        }
        else
        {
            break;
        }
    }
    widget[1] = winValue(mmark,enemymark);

    int tempx , tempy;
    //右斜判断
    mmark = 0;
    enemymark = 0;
    tempx = putX+1;
    tempy = putY-1;
    flag = 0;
    for (int index = 1 ; index < 5 ; index++)
    {
        if (flag == 1)
            break;
        if (tempx < 16 && tempy > 0)
        {
            if (chessBoard[tempx][tempy] == role)
            {
                mmark++;
            }
            else if (chessBoard[tempx][tempy] == !role && chessBoard[tempx][tempy] != -1)
            {
                flag = 1;
                enemymark++;
            }
            else
            {
                break;
            }
            tempx++;
            tempy--;
        }
    }
    tempx = putX-1;
    tempy = putY+1;
    flag = 0;
    for (int index = 1 ; index < 5 ; index++)
    {
        if (flag == 1)
            break;
        if (tempx > 0 && tempy < 16)
        {
            if (chessBoard[tempx][tempy] == role)
            {
                mmark++;
            }
            else if (chessBoard[tempx][tempy] == !role && chessBoard[tempx][tempy] != -1)
            {
                flag = 1;
                enemymark++;
            }
            else
            {
                break;
            }
            tempx--;
            tempy++;
        }
    }
    widget[2] = winValue(mmark,enemymark);

    //左斜判断
    mmark = 0;
    enemymark = 0;
    tempx = putX+1;
    tempy = putY+1;
    flag = 0;
    for (int index = 1 ; index < 5 ; index++)
    {
        if (flag == 1)
            break;
        if (tempx < 16 && tempy < 16)
        {
            if (chessBoard[tempx][tempy] == role)
            {
                mmark++;
            }
            else if (chessBoard[tempx][tempy] == !role && chessBoard[tempx][tempy] != -1)
            {
                flag = 1;
                enemymark++;
            }
            else
            {
                break;
            }
            tempx++;
            tempy++;
        }
    }
    tempx = putX-1;
    tempy = putY-1;
    flag = 0;
    for (int index = 1 ; index < 5 ; index++)
    {
        if (flag == 1)
            break;
        if (tempx > 0 && tempy > 0)
        {
            if (chessBoard[tempx][tempy] == role)
            {
                mmark++;
            }
            else if (chessBoard[tempx][tempy] == !role && chessBoard[tempx][tempy] != -1)
            {
                flag = 1;
                enemymark++;
            }
            else
            {
                break;
            }
            tempx--;
            tempy--;
        }
    }
    widget[3] = winValue(mmark,enemymark);

    int maxwidget = -1;
    for (auto mwidget : widget)
    {
        if (mwidget > maxwidget)
            maxwidget = mwidget;
    }
    return maxwidget;
}
int GomokuBot::winValue(int mmark, int enemymark)
{
    //我方
    if ( (mmark == 5 && enemymark == 0) || (enemymark == 5 && mmark == 0))
    {
        return 100000;
    }
    else if ((mmark == 4 && enemymark == 0) || (enemymark == 4 && mmark == 0))
    {
        return 10000;
    }
    else if ((mmark == 3 && enemymark == 0) || (enemymark == 3 && mmark == 0))
    {
        return 1000;
    }
    else if ((mmark == 2 && enemymark == 0) || (enemymark == 2 && mmark == 0))
    {
        return 100;
    }
    else if ((mmark == 1 && enemymark == 0) || (enemymark == 1 && mmark == 0))
    {
        return 10;
    }
    else if ((mmark == 4 && enemymark == 1) || (enemymark == 4 && mmark == 1))
    {
        return 100;
    }
    else if ((mmark == 3 && enemymark == 1) || (enemymark == 3 && mmark == 1))
    {
        return 100;
    }
    else if ((mmark == 2 && enemymark == 1) || (enemymark == 2 && mmark == 1))
    {
        return 10;
    }
    else
    {
        return 0;
    }
}

void GomokuBot::putChess(int putX, int putY)
{
    bookChess[putX][putY] = true;
    chessBoard[putX][putY] = !mrole;
    reset();
    //qDebug() << "x : " << putX << "y : " << putY;
    int bestPutX , bestPutY;
    int maxWidget = -1;
    //防守判断
    for (int i = 1 ; i < 16 ; i++)
    {
        for (int j = 1; j < 16 ; j++)
        {
            if (bookChess[i][j] == false)
            {
                bookWidget[i][j] = winWidget(i,j,mrole);
                if (bookWidget[i][j] > maxWidget)
                {
                    maxWidget = bookWidget[i][j];
                    bestPutX = i;
                    bestPutY = j;
                }
            }
        }
    }
    qDebug() << "mrole : " << mrole;
    //进攻判断
    for (int i = 1 ; i < 16 ; i++)
    {
        for (int j = 1; j < 16 ; j++)
        {
            if (bookChess[i][j] == false)
            {
                int enemyValue = winWidget(i,j,!mrole);
                if (enemyValue >= bookWidget[i][j] && enemyValue >= maxWidget)
                {
                    bookWidget[i][j] = enemyValue;
                    maxWidget = enemyValue;
                    bestPutX = i;
                    bestPutY = j;
                }
            }
        }
    }
    qDebug() << "mrole : " << !mrole;
    bookChess[bestPutX][bestPutY] = true;
    chessBoard[bestPutX][bestPutY] = mrole;
    emit sendPutChess(bestPutX,bestPutY);
    //qDebug() << bestPutX << bestPutY;
}

