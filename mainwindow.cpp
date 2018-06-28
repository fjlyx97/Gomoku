#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QStringList>
#include <QMessageBox>
#include "qtsocket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋");
    //初始化棋盘
    this->chessboardInit();

    //本地对战
    connect(ui->singerGame,&QPushButton::clicked,this,&MainWindow::singerGame);
    //联机对战
    connect(ui->multiGame,&QPushButton::clicked,this,&MainWindow::qtSocket);
    //人机对战
    connect(ui->botGame,&QPushButton::clicked,this,&MainWindow::botGame);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chessboardInit()
{
    this->role = 1;
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
            row[i] = 38;
            col[i] = 53;
        }
        else
        {
            row[i] = row[i-1] + 52;
            col[i] = col[i-1] + 49;
        }
    }
    isTcpConnect = false;
    isMulGame = false;
    isBotGame = false;
    isTurn = true;
}
//键盘点击事件
void MainWindow::mousePressEvent(QMouseEvent * e)
{
    int putX = e->x();
    int putY = e->y();
    if (isTcpConnect) //如果是tcp发送请求
    {
        //qDebug() << isTurn;
        if (isTurn)
        {
            if (isInChessboard(putX,putY))
            {
                QString content;
                isTurn = false;
                content = "true,";
                QString msg = content + QString::number(putX) + ',' + QString::number(putY);
                tcpSocket->write(msg.toUtf8());
                tcpSocket->flush();
                runGame(putX,putY);
            }
        }
    }
    else if (isMulGame)
    {
        runGame(putX,putY);
    }
    else if (isBotGame)
    {
        if (isTurn)
        {
            runGame(putX,putY);
        }
    }
}

void MainWindow::runGame(int putX, int putY)
{
    int ansX = 0;
    int ansY = 0;
    QPixmap black(":/new/bg1/image/black.png");
    QPixmap white(":/new/bg1/image/white.png");
    QLabel* chess = new QLabel(this);
    int tempx , tempy;


    if (isGameBegin)
    {
        for (int i = 1 ; i < 16 ; i++)
        {
            for (int j = 1 ; j < 16 ; j++)
            {
                if ( abs(putX-row[i]) < 20 && abs(putY-col[j]) < 20 )
                {
                    ansX = row[i] - 13;
                    ansY = col[j] - 13;
                    tempx = row[i];
                    tempy = col[j];
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
        int bookx = (tempx-38) / 50 + 1; //人工测距
        int booky = (tempy-53) / 50 + 1;
        //qDebug() << "ans : " << ansX << " " << ansY;
        //qDebug() << bookx << " " << booky;
        //测试棋盘
        /*
        for (int t = 1 ; t < 16 ; t++)
        {
            for (int k = 1 ; k < 16 ; k++)
            {
                qDebug() << chessboard[t][k] << " ";
            }
            qDebug() << endl;
        }
        */

        if (ansX != 0 && ansY != 0 && chessboard[bookx][booky] == -1)
        {
            chess->setGeometry(ansX,ansY,30,30);
            chess->setScaledContents(true);
            labels.push_back(chess);
            chess->show();
            chessboard[bookx][booky] = role;


            for (int i = 1 ; i < 16 ; i++)
            {
                for (int j = 1 ; j < 16 ; j++)
                {
                    //判断胜利 还原环境
                    if (ifWin(role,i,j))
                    {
                        if (role == 0)
                            ui->who->setText("游戏结束，黑方获胜");
                        else
                            ui->who->setText("游戏结束，白方获胜");
                        ui->singerGame->setDisabled(false);
                        ui->botGame->setDisabled(false);
                        ui->multiGame->setDisabled(false);
                        // 初始化游戏
                        if (isBotGame)
                            delete mBot;

                        /*
                        if (isTcpConnect)
                        {
                            tcpServer->close();
                            tcpSocket->close();
                        }
                        */

                        this->isTcpConnect = false;
                        this->isMulGame = false;
                        this->isBotGame = false;
                        isGameBegin = false;
                        return;

                    }
                }
            }
            role = !role;

            //机器人下棋
            if (isBotGame && isTurn)
            {
                isTurn = false;
                emit sendToBot(bookx,booky);
            }
            if (!isTcpConnect)
            {
                if (role == 0)
                    ui->who->setText("轮到黑方");
                else
                    ui->who->setText("轮到白方");
            }
            else
            {
                ui->who->setText("轮到对方");
            }
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
    this->isMulGame = true;
    ui->singerGame->setDisabled(true);
    ui->multiGame->setDisabled(true);
    ui->botGame->setDisabled(true);
    ui->who->setText("游戏开始...");
    this->resetGame();
}

bool MainWindow::ifWin(int role , int x , int y)
{
    //九宫格判断
    int flag[8];
    for (int i = 0 ; i < 8 ; i++)
        flag[i] = 1;
    //往右边
    for (int i = x ; i < x+5 ; i++)
    {
        if (chessboard[i][y] != role || i > 15)
        {
            flag[0] = 0;
            break;
        }
    }
    //往下边
    for (int i = y ; i < y+5; i++)
    {
        if (chessboard[x][i] != role || i > 15)
        {
            flag[1] = 0;
            break;
        }
    }
    //往左边
    for (int i = x ; i > x-5 ; i--)
    {
        if (chessboard[i][y] != role || i < 1)
        {
            flag[2] = 0;
            break;
        }
    }
    //往上边
    for (int i = y ; i > y-5 ; i--)
    {
        if (chessboard[x][i] != role || i < 1)
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

void MainWindow::resetGame()
{
    role = !role;
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
            row[i] = 38;
            col[i] = 53;
        }
        else
        {
            row[i] = row[i-1] + 52;
            col[i] = col[i-1] + 50;
        }
    }
    QVector<QLabel*>::iterator ite;
    for (ite = labels.begin() ; ite != labels.end() ; ite++)
    {
        (*ite)->close();
    }
    labels.clear();
}

void MainWindow::qtSocket()
{
    QtSocket connectWidget(this,&tcpServer,&tcpSocket);
    connect(&connectWidget,&QtSocket::connectSuccess,this,&MainWindow::acceptConnectSignal);
    connect(&connectWidget,&QtSocket::isClient,this,&MainWindow::acceptClient);
    connectWidget.exec();
}

void MainWindow::acceptConnectSignal(bool misTcpConnect)
{
    this->isTcpConnect = misTcpConnect;
    if (isTcpConnect)
    {
        ui->singerGame->setDisabled(true);
        ui->multiGame->setDisabled(true);
        ui->botGame->setDisabled(true);
        ui->who->setText("游戏开始...");
        resetGame();
        isTurn = true;
        if (isTurn)
            ui->who->setText("轮到自己");
        else
            ui->who->setText("轮到对方");
        //qDebug() << "Server " << tcpSocket->state();
        //qDebug() << "role " << role;
        //qDebug() << "isTurn " << isTurn;
        connect(this->tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::recvPos);
        connect(this->tcpSocket,&QTcpSocket::disconnected,this,&MainWindow::tcpDisconnect);
    }
}

void MainWindow::recvPos()
{
    QByteArray buffer;
    buffer = tcpSocket->readAll();
    if(!buffer.isEmpty())
    {
        QString recvPoint = tr(buffer);
        QStringList mPoint = recvPoint.split(',');

        int posX , posY;
        posX = mPoint[1].toInt();
        posY = mPoint[2].toInt();
        runGame(posX,posY);
        isTurn = true;
        if (isGameBegin)
            ui->who->setText("轮到自己");
    }
}

void MainWindow::tcpDisconnect()
{
    QMessageBox::about(this,"警告","已和对方失去连接");
    ui->singerGame->setDisabled(false);
    ui->multiGame->setDisabled(false);
    ui->botGame->setDisabled(false);
    ui->who->setText("等待游戏重新开始");
    qtSocket();
}

void MainWindow::acceptClient(bool misTcpConnect)
{
    this->isTcpConnect = misTcpConnect;
    if (isTcpConnect)
    {
        ui->singerGame->setDisabled(true);
        ui->multiGame->setDisabled(true);
        ui->botGame->setDisabled(true);
        ui->who->setText("游戏开始...");
        resetGame();
        isTurn = false;
        if (isTurn)
            ui->who->setText("轮到自己");
        else
            ui->who->setText("轮到对方");

        //qDebug() << "client " << tcpSocket->state();
        //qDebug() << "role " << role;
        //qDebug() << "isTurn " << isTurn;

        connect(this->tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::recvPos);
        connect(this->tcpSocket,&QTcpSocket::disconnected,this,&MainWindow::tcpDisconnect);
    }
}

bool MainWindow::isInChessboard(int putX ,int putY)
{
    int ansX = 0;
    int ansY = 0;
    int tempx , tempy;
    for (int i = 1 ; i < 16 ; i++)
    {
        for (int j = 1 ; j < 16 ; j++)
        {
            if ( abs(putX-row[i]) < 20 && abs(putY-col[j]) < 20 )
            {
                ansX = row[i] - 13;
                ansY = col[j] - 13;
                tempx = row[i];
                tempy = col[j];
                //qDebug() << "row col:" << row[i] <<  col[j] << endl;
                break;
            }
        }
    }
    int bookx = (tempx-38) / 50 + 1; //人工测距
    int booky = (tempy-53) / 50 + 1;
    if (ansX != 0 && ansY != 0 && chessboard[bookx][booky] == -1)
        return true;
    else
        return false;
}

void MainWindow::botGame()
{
    this->resetGame();
    isBotGame = true;
    isGameBegin = true;
    ui->singerGame->setDisabled(true);
    ui->multiGame->setDisabled(true);
    ui->botGame->setDisabled(true);
    ui->who->setText("游戏开始...");
    //初始化Bot
    mBot = new GomokuBot(!role);
    mBot->reset();
    connect(this,&MainWindow::sendToBot,mBot,&GomokuBot::putChess);
    connect(mBot,&GomokuBot::sendPutChess,this,&MainWindow::recBotChess);
}

void MainWindow::recBotChess(int putX, int putY)
{
    qDebug() << "Bot x : " << putX << "Bot y : " << putY;
    runGame(row[putX],col[putY]);
    isTurn = true;
}
