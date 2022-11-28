#ifndef BIOGRAPHY_H
#define BIOGRAPHY_H

#include <QWidget>

namespace Ui {
class Biography;
}

class Biography : public QWidget
{
    Q_OBJECT

public:
    explicit Biography(QWidget *parent = nullptr);
    ~Biography();

private:
    Ui::Biography *ui;
};

#endif // BIOGRAPHY_H
