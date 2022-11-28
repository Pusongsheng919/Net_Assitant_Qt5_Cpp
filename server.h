#ifndef SERVER_H
#define SERVER_H
#include<QTcpServer>
#include<QTcpSocket>
#include"widget.h"
#include <QWidget>

class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
private slots:
    void on_startServer_clicked();
    void on_sendMsg_clicked();
private:
    QTcpServer * tcp;
    QTcpSocket * skt;

signals:

};

#endif // SERVER_H
