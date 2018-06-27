#ifndef QTSOCKET_H
#define QTSOCKET_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class QtSocket;
}

class QtSocket : public QDialog
{
    Q_OBJECT

public:
    explicit QtSocket(QWidget *parent = 0 , QTcpServer** tcpServer = NULL, QTcpSocket** tcpSocket = NULL);
    ~QtSocket();
    void createServer();
    void connectServer();
    void newConnect();

signals:
    void connectSuccess(bool isConnect);
    void isClient(bool isConnect);

private:
    Ui::QtSocket *ui;
    QString localHostName;
    QHostInfo localInfo;
    QTcpServer** mtcpServer;
    QTcpSocket** mtcpSocket;
};

#endif // QTSOCKET_H
