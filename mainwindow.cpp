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
            chessboard[i][j] = 0;
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
    ui->test->setText(tr("(%1,%2)").arg(e->x()).arg(e->y()));
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
        if (ansX != 0 && ansY != 0)
        {
            role = !role;
            chess->setGeometry(ansX,ansY,28,28);
            chess->show();
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
