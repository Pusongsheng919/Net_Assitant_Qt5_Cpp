#include "server.h"

Server::Server(QWidget *parent) : QWidget(parent)
{
    this->tcp = new QTcpServer(this);
    connect (this->tcp,&QTcpServer::newConnection,this,[=](){
       this->skt = this->tcp->nextPendingConnection();

    });
}


void Server::on_startServer_clicked()
{

}

void Server::on_sendMsg_clicked()
{

}
