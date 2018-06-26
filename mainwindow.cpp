#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化棋盘
    this->chessboardInit();

    //添加游戏背景图片
    QPalette palette;
    QPixmap bg(":/new/bg/image/chessboard.bmp");
    palette.setBrush(backgroundRole(),QBrush(bg.scaled(this->size())));
    this->setPalette(palette);

    //加载游戏

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chessboardInit()
{
    for (int i = 1 ; i < 16 ; i++)
    {
        for (int j = 1 ; j < 16 ; j++)
        {
            chessboard[i][j] = -1;
        }
    }
    for (int i = 1 ; i < 16 ; i++)
    {
        if (i == 1)
        {
            row[i] = 117;
            col[i] = 120;
        }
        else
        {
            row[i] = row[i-1] + 48;
            col[i] = col[i-1] + 40;
        }
    }
    isGameBegin = true;
}
//键盘点击事件
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    //ui->test->setText(tr("(%1,%2)").arg(e->x()).arg(e->y()));
    int putX = e->x();
    int putY = e->y();
    int ansX = 0;
    int ansY = 0;
    QPixmap black(":/new/bg/image/black.bmp");
    QPixmap white(":/new/bg/image/white.bmp");
    QLabel* chess = new QLabel(this);


    if (isGameBegin)
    {
        for (int i = 1 ; i < 16 ; i++)
        {
            for (int j = 1 ; j < 16 ; j++)
            {
                if ( abs(putX-row[i]) < 10 && abs(putY-col[j]) < 10 )
                {
                    ansX = row[i] - 14;
                    ansY = col[j] - 14;
                    //qDebug() << "row col:" << row[i] <<  col[j] << endl;
                    break;
                }
            }
        }
        if (role == 0) //黑
        {
            chess->setPixmap(black);
        }
        else	//白
        {
            chess->setPixmap(white);
        }
        int bookx = (ansX-100) / 48 + 1; //人工测距
        int booky = (ansY-100) / 40 + 1;
        if (ansX != 0 && ansY != 0 && chessboard[bookx][booky] == -1)
        {
            chess->setGeometry(ansX,ansY,30,30);
            chess->show();
            chessboard[bookx][booky] = role;
            if (ifWin(role,bookx,booky))
            {
                if (role == 0)
                    ui->who->setText("游戏结束，黑方获胜");
                else
                    ui->who->setText("游戏结束，白方获胜");
                return;
            }

            role = !role;
            if (role == 0)
                ui->who->setText("轮到黑方");
            else
                ui->who->setText("轮到白方");

            //qDebug() << putX <<  putY << endl;
        }
        else
        {
            delete chess;
        }
    }
}

void MainWindow::singerGame()
{
    this->isGameBegin = true;
}

bool MainWindow::ifWin(int role , int x , int y)
{
    //九宫格判断
    int flag[8];
    for (int i = 0 ; i < 8 ; i++)
        flag[i] = 1;
    //往右边
    for (int i = x ; i < 16 && i < x+5 ; i++)
    {
        if (chessboard[i][y] != role)
        {
            flag[0] = 0;
            break;
        }
    }
    //往下边
    for (int i = y ; i < 16 && i < y+5; i++)
    {
        if (chessboard[x][i] != role)
        {
            flag[1] = 0;
            break;
        }
    }
    //往左边
    for (int i = x ; i > 0 && i > x-5 ; i--)
    {
        if (chessboard[i][y] != role)
        {
            flag[2] = 0;
            break;
        }
    }
    //往上边
    for (int i = y ; i > 0 && i > y-5 ; i--)
    {
        if (chessboard[x][i] != role)
        {
            flag[3] = 0;
            break;
        }
    }

    int temp_x , temp_y;
    //往右上
    temp_x = x;
    temp_y = y;
    for (int index = 1 ; index <= 5 ; index++)
    {
        if (chessboard[temp_x][temp_y] != role)
        {
            flag[4] = 0;
            break;
        }
        temp_x++;
        temp_y--;
        if (temp_x > 15 || temp_y < 1)
        {
            flag[4] = 0;
            break;
        }
    }
    //往右下
    temp_x = x;
    temp_y = y;
    for (int index = 1 ; index <= 5 ; index++)
    {
        if (chessboard[temp_x][temp_y] != role)
        {
            flag[5] = 0;
            break;
        }
        temp_x++;
        temp_y++;
        if (temp_x > 15 || temp_y > 15)
        {
            flag[5] = 0;
            break;
        }
    }
    //往左下
    temp_x = x;
    temp_y = y;
    for (int index = 1 ; index <= 5 ; index++)
    {
        if (chessboard[temp_x][temp_y] != role)
        {
            flag[6] = 0;
            break;
        }
        temp_x--;
        temp_y++;
        if (temp_x < 1 || temp_y > 15)
        {
            flag[6] = 0;
            break;
        }
    }
    //往左上
    temp_x = x;
    temp_y = y;
    for (int index = 1 ; index <= 5 ; index++)
    {
        if (chessboard[temp_x][temp_y] != role)
        {
            flag[7] = 0;
            break;
        }
        temp_x--;
        temp_y--;
        if (temp_x < 1 || temp_y < 1)
        {
            flag[7] = 0;
            break;
        }
    }
    //判断是否获胜
    for (auto t : flag)
    {
        if ( t == 1 )
        {
            return true;
        }
    }
    return false;
}

