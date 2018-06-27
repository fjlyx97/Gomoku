#include "qtsocket.h"
#include "ui_qtsocket.h"
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

QtSocket::QtSocket(QWidget *parent , QTcpServer** tcpServer , QTcpSocket** tcpSocket) :
    QDialog(parent),
    ui(new Ui::QtSocket)
{
    ui->setupUi(this);
    //进行初始化
    this->setWindowTitle("服务器");
    localHostName = QHostInfo::localHostName();
    localInfo = QHostInfo:: fromName(localHostName);
    mtcpServer = tcpServer;
    mtcpSocket = tcpSocket;
    //设置ip为本机IP
    //ui->ipContent->setText(localInfo.addresses()[0].toString());
    ui->ipContent->setText("127.0.0.1");
    ui->portContent->setText("8000");
    connect(ui->createServer,&QPushButton::clicked,this,&QtSocket::createServer);
    connect(ui->connectServer,&QPushButton::clicked,this,&QtSocket::connectServer);
}

QtSocket::~QtSocket()
{
    delete ui;
}

void QtSocket::createServer()
{
    *mtcpServer = new QTcpServer();
    if (!(*mtcpServer)->listen(QHostAddress::Any,ui->portContent->text().toInt()))
    {
        QMessageBox::about(this,"错误","服务器创建失败");
        this->close();
    }
    else
    {
        connect(*mtcpServer,&QTcpServer::newConnection,this,&QtSocket::newConnect);
        QMessageBox::about(this,"正确","服务器创建成功");
    }
}

void QtSocket::newConnect()
{
    *mtcpSocket = (*mtcpServer)->nextPendingConnection();
    emit connectSuccess(true);
}

void QtSocket::connectServer()
{
    *mtcpSocket = new QTcpSocket();
    //qDebug() << ui->ipContent->text();
    (*mtcpSocket)->connectToHost(ui->ipContent->text(),ui->portContent->text().toInt());
    //qDebug() << "socket :: " << (*mtcpSocket)->state();
    if (!(*mtcpSocket)->waitForConnected(15000))
    {
        QMessageBox::about(this,"警告","服务器连接失败");
    }
    else
    {
        QMessageBox::about(this,"成功","服务器连接成功");
        emit isClient(true);
    }
}
