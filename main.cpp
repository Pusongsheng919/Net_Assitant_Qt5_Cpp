#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("网络调试助手"); //设置窗口名
    w.setFixedSize(800,600);
    w.show();
    return a.exec();
}
