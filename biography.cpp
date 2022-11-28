#include "biography.h"
#include "ui_biography.h"

Biography::Biography(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Biography)
{
    ui->setupUi(this);
    this->setWindowTitle("关于作者");
}

Biography::~Biography()
{
    delete ui;
}
