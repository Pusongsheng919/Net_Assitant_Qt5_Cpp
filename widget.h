#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"biography.h"
#include<QString>
#include<QTcpServer>
#include<QTcpSocket>
#include<QUdpSocket>
#include <QButtonGroup>
#include<QPushButton>
#include<QDebug>
#include<QMessageBox>
#include<QComboBox>
#include<QByteArray>
#include <QHostAddress>
#include<QString>
#include<QNetworkProxy>
#include<QTimer>
#include<QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //服务器函数
    void on_startServer_clicked();
    void on_sendMsg_clicked();
    //客户端函数
    void on_connectServer_clicked();
    void on_sendMsg_clicked_client();
    void on_disconnect_clicked();

    int Client_num = 1;
private slots:
    //网络协议类型选择
    void on_comboBox_currentIndexChanged(int index); //index下拉框的索引

    //单选框1
    void Slots_RadioBox1();
    //单选框2
    void Slots_RadioBox2();
    //清空单选Flag
    void ClearRadio_1();
    void ClearRadio_2();

    //UDP
    //点击发送信号函数
    void On_PushButton_Clicked();


private:
    Ui::Widget *ui;
    //服务器指针对象
    QTcpServer* m_server;
    QTcpSocket* m_tcp;
    //客户端指针对象
    QTcpSocket* m_tcp2;
    //单选框分组
    QButtonGroup *groupButton1;
    QButtonGroup *groupButton2;
    //单选框Flag
    int radio1;
    int radio2;
    int radio3;
    int radio4;
    int radio5;
    int radio6;
    int radio7;
    int radio8;

    //保存到文件 文件对象
    QFile * qfile;

    //UDP socket对象
    QUdpSocket * m_sent; //UDP发送端
};
#endif // WIDGET_H
