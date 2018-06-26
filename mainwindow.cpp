#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

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
        if (i == 1 && j == 1)
        {
            row[i] = 117;
            col[i] = 120;
        }
        else
        {
            row[i] = row[i-1] + 40;
        }
    }
}
//键盘点击事件
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    //ui->test->setText(tr("(%1,%2)").arg(e->x()).arg(e->y()));
    int putX = e->x();
    int putY = e->y();
    if (isGameBegin)
    {
        if (role == 0) //黑
        {

        }
        else	//白
        {

        }
    }
}

void MainWindow::singerGame()
{
    this->isGameBegin = True;
}
