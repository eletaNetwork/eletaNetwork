#ifndef ELETATECHINIT_H
#define ELETATECHINIT_H

#include <QDialog>

namespace Ui {
class EltTechInit;
}

class EltTechInit : public QDialog
{
    Q_OBJECT

public:
    explicit EltTechInit(QWidget *parent = 0);
    ~EltTechInit();
    QString GetServers();
    void ShowEletatechIntro(bool exitAfter = true);

private:
    Ui::EltTechInit *ui;
};

#endif // ELETATECHINIT_H
