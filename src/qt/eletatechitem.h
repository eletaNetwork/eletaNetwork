#ifndef ELETATECHITEM_H
#define ELETATECHITEM_H

#include <QWidget>

namespace Ui {
class eletatechitem;
}

class eletatechitem : public QWidget
{
    Q_OBJECT

public:
    explicit eletatechitem(QWidget *parent = 0);
    ~eletatechitem();
    void setHost(QString hostStr);
    void setName(QString nameStr);

private:
    Ui::eletatechitem *ui;
    QString host;
    QString name;
};

#endif // ELETATECHITEM_H
