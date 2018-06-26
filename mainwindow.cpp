#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
