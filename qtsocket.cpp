#include "qtsocket.h"
#include "ui_qtsocket.h"
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

QtSocket::QtSocket(QWidget *parent):
    QDialog(parent),
    ui(new Ui::QtSocket)
{
    ui->setupUi(this);
    //进行初始化
    this->setWindowTitle("服务器");
    localHostName = QHostInfo::localHostName();
    localInfo = QHostInfo:: fromName(localHostName);
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
    mtcpServer = new QTcpServer();
    if (!mtcpServer->listen(QHostAddress::LocalHost,ui->portContent->text().toInt()))
    {
        QMessageBox::about(this,"错误","服务器创建失败");
        this->close();
    }
    else
    {
        connect(mtcpServer,&QTcpServer::newConnection,this,&QtSocket::newConnect);
        QMessageBox::about(this,"正确","服务器创建成功");
    }
}

void QtSocket::newConnect()
{
    mtcpSocket = mtcpServer->nextPendingConnection();
    mtcpServer->close();
    mtcpSocket->write("test");
    //emit connectSuccess(true);
}

void QtSocket::connectServer()
{

}
