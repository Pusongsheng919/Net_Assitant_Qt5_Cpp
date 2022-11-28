#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //主ui界面及图标
    ui->setupUi(this);
    ui->label_5->setPixmap(QPixmap(":/NetAss_Icons/version.png").scaled(30,30));
    ui->Logo->setPixmap(QPixmap(":/NetAss_Icons/mainicon.png").scaled(40,40));
    ui->label_12_status->setPixmap(QPixmap(":/NetAss_Icons/mainicon_2.png").scaled(30,30));

    //清理对话框
    connect (ui->pushButton_2_ClearRec,&QPushButton::clicked,this,[=](){
        ui->textEdit_RecData->clear();
    });
    //清理聊天框
    connect (ui->pushButton_2_ClearRec_2,&QPushButton::clicked,this,[=](){
        ui->textEdit_2_SentData->clear();
    });
    //关于作者
    connect (ui->pushButton_2,&QPushButton::clicked,this,[=](){
            Biography * bio = new Biography;
            bio->show();
    });

    //初始化单选按钮
     groupButton1=new QButtonGroup(this);
     groupButton1->addButton(ui->radioButton,0);
     groupButton1->addButton(ui->radioButton_2,1);
     groupButton1->addButton(ui->radioButton_3,2);
     groupButton1->addButton(ui->radioButton_4,3);
     groupButton1->addButton(ui->radioButton_8,4);

     groupButton2=new QButtonGroup(this);
     groupButton2->addButton(ui->radioButton_5,0);
     groupButton2->addButton(ui->radioButton_6,1);
     groupButton2->addButton(ui->radioButton_7,2);
     //构造单选框槽函数
     //Box1
     connect(ui->radioButton,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox1()));
     connect(ui->radioButton_2,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox1()));
     connect(ui->radioButton_3,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox1()));
     connect(ui->radioButton_4,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox1()));
     connect(ui->radioButton_8,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox1()));

     //Box2
     connect(ui->radioButton_5,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox2()));
     connect(ui->radioButton_6,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox2()));
     connect(ui->radioButton_7,SIGNAL(clicked(bool)),this,SLOT(Slots_RadioBox2()));


}

//实现单选框槽函数
//清空单选框信号
void Widget::ClearRadio_1()
{
    this->radio1 = 0;
    this->radio2 = 0;
    this->radio3 = 0;
    this->radio4 = 0;
    this->radio8 = 0;
}

void Widget::ClearRadio_2()
{
    this->radio5 = 0;
    this->radio6 = 0;
    this->radio7 = 0;
}

//单选框1
void Widget::Slots_RadioBox1()
{
    switch(groupButton1->checkedId())
    {
    case 0:
    {
        this->ClearRadio_1();
        this->radio1 = 1;
        break;
    }
    case 1:
    {
        this->ClearRadio_1();
        this->radio2 = 1;
        break;
    }
    case 2:
    {
        this->ClearRadio_1();
        this->radio3 = 1;
        break;
    }
    case 3:
    {
        this->ClearRadio_1();
        this->radio4 = 1;
        break;
    }
    case 4:
    {
        this->ClearRadio_1();
        this->radio8 = 1;
        break;
    }
    }

}

//单选框2
void Widget::Slots_RadioBox2()
{
    switch(groupButton2->checkedId())
    {
    case 0:
    {
        this->ClearRadio_2();
        this->radio5 = 1;
        break;
    }
    case 1:
    {
        this->ClearRadio_2();
        this->radio6 = 1;
        break;
    }
    case 2:
    {
        this->ClearRadio_2();
        this->radio7 = 1;
        break;
    }
    }

}



Widget::~Widget()
{
    delete ui;
}


//服务器函数
void Widget::on_startServer_clicked()
{
    unsigned short port = ui->lineEdit_2->text().toInt();
    // 设置服务器监听
    this->m_server->listen(QHostAddress::Any, port);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
//    ui->pushButton->setEnabled(false);
}

void Widget::on_sendMsg_clicked()
{
    if(this->radio7 == 1) //循环发送
    {
        static int cir_Server = 0;
        cir_Server++;
        ui->pushButton_sent->setText("停止");
        int wait_time = ui->lineEdit_3->text().toInt(); //读取用户输入的循环周期
        bool flag = true;
        while (flag)
        {
            if(cir_Server %2 ==0) //再次点击退出循环
            {
                ui->pushButton_sent->setText("发送");
                break;
            }
            QString sendMsg = ui->textEdit_2_SentData->toPlainText();
            m_tcp->write(sendMsg.toUtf8());
            if(this->radio6 == 1) //HEX二进制发送显示
            {
                ui->textEdit_RecData->append("服务器：" + sendMsg.toUtf8().toHex());
            }
            else ui->textEdit_RecData->append("服务器：" + sendMsg);

            //等待事件
            QEventLoop loop;//定义一个新的事件循环
            QTimer::singleShot(wait_time, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
            loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
        }

    }
    else //单发
    {
        QString sendMsg = ui->textEdit_2_SentData->toPlainText();

        m_tcp->write(sendMsg.toUtf8());
        if(this->radio6 == 1) //HEX二进制发送显示
        {
            ui->textEdit_RecData->append("服务器：" + sendMsg.toUtf8().toHex());
        }
        else ui->textEdit_RecData->append("服务器：" + sendMsg);
        ui->textEdit_2_SentData->clear();
    }

}



//客户端函数
void Widget::on_connectServer_clicked()
{
    QString ip = ui->lineEdit->text();
    unsigned short port = ui->lineEdit_2->text().toInt();
    m_tcp2->connectToHost(QHostAddress(ip), port);
}

void Widget::on_sendMsg_clicked_client()
{
    //循环发送
    if(this->radio7 == 1)
    {

        static int cir_sent = 0;
        cir_sent++;

        ui->pushButton_sent->setText("停止");

        int wait_time = ui->lineEdit_3->text().toInt(); //读取用户输入的循环周期
        bool flag = true;
        while (flag)
        {
            if(cir_sent%2 == 0) //再次点击按钮 退出循环
            {
                ui->pushButton_sent->setText("发送");
                break;
            }

            QString sendMsg = ui->textEdit_2_SentData->toPlainText();
            m_tcp2->write(sendMsg.toUtf8());
            if(this->radio6 == 1)
            {
                ui->textEdit_RecData->append("客户端:" + sendMsg.toUtf8().toHex());
            }
            else ui->textEdit_RecData->append("客户端:" + sendMsg);
            //等待事件
            QEventLoop loop;//定义一个新的事件循环
            QTimer::singleShot(wait_time, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
            loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
        }

    }
    else
    {
        QString sendMsg = ui->textEdit_2_SentData->toPlainText();
        m_tcp2->write(sendMsg.toUtf8());
        if(this->radio6 == 1)
        {
            ui->textEdit_RecData->append("客户端:" + sendMsg.toUtf8().toHex());
        }
        else ui->textEdit_RecData->append("客户端:" + sendMsg);
        ui->textEdit_2_SentData->clear();
    }
}

void Widget::on_disconnect_clicked()
{
     m_tcp2->close();
     ui->lineEdit->setEnabled(true);
     ui->lineEdit_2->setEnabled(true);
}


//UDP函数
//点击发送信号函数
void Widget::On_PushButton_Clicked()
{

    QByteArray dataGram = ui->lineEdit_4->text().toUtf8(); //读取待发送数据报的文本信息
    QString Udp_sentMass = dataGram;
    unsigned short port = ui->lineEdit_2->text().toInt(); //读取端口信息
    this->m_sent->writeDatagram(dataGram.data(),dataGram.size(),QHostAddress::Broadcast,port); //将端口信息写入套接字数据报
    ui->lineEdit_4->clear(); //清理广播屏
//    ui->textEdit_RecData->setText("本机发送：" + Udp_sentMass);
    if(this->radio6 == 1) //HEX格式显示数据
    {
        ui->textEdit_RecData->append("本机发送：" + dataGram.toHex());
    }
    else ui->textEdit_RecData->append("本机发送：" + Udp_sentMass);
}


//下拉框 网络协议类型选择
void Widget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0) //UDP
    {
        //提示信息
        ui->textEdit_RecData->append("网络小助手提示您：由于UDP是一种无连接、不可靠、面向数据报的网络协议，所以本助手所显示的数据为本地发送记录~");
        ui->textEdit_RecData->append("该记录仅代表您所发消息，不代表接收方已成功接收~");
        ui->lineEdit_4->setEnabled(true);

        //关闭IP输入框 默认主机广播地址
        ui->lineEdit->setText("默认主机广播地址");
        ui->lineEdit->setEnabled(false); //锁死IP地址框
        ui->pushButton->setEnabled(false); //锁死连接网络按钮
        ui->textEdit_2_SentData->setEnabled(false); //锁死TCP通讯发送框

        //创建一个UDP对象
        this->m_sent = new QUdpSocket(this);

        //点击发送按钮 调用发送函数
        connect (ui->pushButton_3,&QPushButton::clicked,this,[=](){
            if(index == 0) this->On_PushButton_Clicked();
        });
    }
    else if(index == 1) //TCP Server
    {

        //接收数据保存到本地文件槽函数 点击该单选项则打开一个文件
        connect (ui->radioButton_4,&QRadioButton::clicked,this,[=](){
            QString path = QFileDialog::getOpenFileName(this,"打开文件","E:\\");
            //可写的方式打开文件
            qfile = new QFile(path);
        });

        //相应lineEdit设置
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);

        //网络连接按钮
        connect (ui->pushButton,&QPushButton::clicked,this,[=](){
            this->on_startServer_clicked();
        });

            // 创建 QTcpServer 对象
            m_server = new QTcpServer(this);
            // 检测是否有新的客户端连接
            connect(m_server, &QTcpServer::newConnection, this, [=](){
                m_tcp = m_server->nextPendingConnection();
                ui->textEdit_RecData->append("成功与客户端建立新连接 ...");
                ui->label_12_status->setPixmap(QPixmap(":/NetAss_Icons/successful.png").scaled(30,30));
                // 检测是否有客户端数据
                       connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
                       {
                           // 接收数据
                           QByteArray recvMsg = m_tcp->readAll();
                           if(this->radio3 != 1) //this->radio3为1 则不显示接收消息
                           {
                               if(this->radio2 == 1)
                               {
                                   ui->textEdit_RecData->append("客户端：" + recvMsg.toHex());
                               }
                               else ui->textEdit_RecData->append("客户端：" + recvMsg);
                           }
                           if(this->radio4 == 1) //同上为并列关系 不可以if else
                           {
                               qfile->open(QIODevice::Append); //Append追加的方式打开文件
                               qfile->write(recvMsg);
                               qfile->close();
                           }
                           //this->radio8 不显示接收消息为空实现 不选择radio3即可
                       });
                       // 客户端断开了连接
                       connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
                       {
                           ui->textEdit_RecData->append("客户端已经断开连接 ...");
//                           m_tcp->deleteLater();
                           ui->label_12_status->setPixmap(QPixmap(":/NetAss_Icons/disconnect.png").scaled(30,30));
                       });
            });

            //消息发送按钮 -- 循环发送
            connect (ui->pushButton_sent,&QPushButton::clicked,this,[=](){
                if(index == 1) this->on_sendMsg_clicked();
            });
    }
    else if(index == 2) //TCP Client
    {
        //点击接收数据保存到本地文件
        connect (ui->radioButton_4,&QRadioButton::clicked,this,[=](){
            QString path = QFileDialog::getOpenFileName(this,"打开文件","E:\\");
            //可写的方式打开文件
            qfile = new QFile(path);
        });


        //相应lineEdit设置
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_4->setEnabled(false);

        //网络连接按钮
        connect (ui->pushButton,&QPushButton::clicked,this,[=](){

            if(Client_num%2 == 0) this->on_disconnect_clicked();
            else this->on_connectServer_clicked();
            Client_num++;
//            this->on_connectServer_clicked();
        });

        // 创建通信的套接字对象
        m_tcp2 = new QTcpSocket(this);
        m_tcp2->setProxy(QNetworkProxy::NoProxy); //将默认代理类型修改为 无代理问题 （删除程序直接GG）
            // 检测是否和服务器是否连接成功了
               connect(m_tcp2, &QTcpSocket::connected, this, [=]()
               {
                   ui->pushButton->setText("关闭连接");
                   ui->lineEdit->setEnabled(false);
                   ui->lineEdit_2->setEnabled(false);
                   ui->textEdit_RecData->append("服务器连接成功 ！！！");
                   ui->label_12_status->setPixmap(QPixmap(":/NetAss_Icons/successful.png").scaled(30,30));
               });

               // 检测服务器是否回复了数据
                   connect(m_tcp2, &QTcpSocket::readyRead, this , [=]()
                   {
                       // 接收服务器发送的数据
                       QByteArray recvMsg = m_tcp2->readAll();
                       if(this->radio3 != 1) //this->radio3为1 则不显示接收消息
                       {
                           if(this->radio2 == 1 || this->radio6 == 1)
                           {
                               ui->textEdit_RecData->append("服务器：" + recvMsg.toHex());
                           }
                           else ui->textEdit_RecData->append("服务器：" + recvMsg);
                       }

                       if(this->radio4 == 1) //同上为并列关系 不可以if else
                       {
                           qfile->open(QIODevice::Append); //Append追加的方式打开文件
                           qfile->write(recvMsg);
                           qfile->close();
                       }
                       //this->radio8 显示接收消息为空实现 只要不点不显示消息就可以
                   });

               // 检测服务器是否和客户端断开了连接
                   connect(m_tcp2, &QTcpSocket::disconnected, this, [=]()
                   {
                       ui->pushButton->setText("网络连接");
                       ui->textEdit_RecData->append("服务器连接已断开 ...");
                        ui->label_12_status->setPixmap(QPixmap(":/NetAss_Icons/disconnect.png").scaled(30,30));
                       ui->lineEdit->setEnabled(true);
                       ui->lineEdit_2->setEnabled(true);
                   });

                   //消息发送按钮 -- 循环发送
                   connect (ui->pushButton_sent,&QPushButton::clicked,this,[=](){
                       if(index == 2) this->on_sendMsg_clicked_client();
                   });

    }
}




