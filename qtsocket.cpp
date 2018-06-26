#include "qtsocket.h"
#include "ui_qtsocket.h"
#include <QLineEdit>
#include <QPushButton>

QtSocket::QtSocket(QWidget *parent , QTcpServer* tcpServer , QTcpSocket* tcpSocket) :
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
    ui->ipContent->setText(localInfo.addresses()[0].toString());
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
    if (!mtcpServer->listen(QHostAddress::LocalHost,ui->portContent->text()))
    {
        this->close();
    }
}

void QtSocket::connectServer()
{

}
