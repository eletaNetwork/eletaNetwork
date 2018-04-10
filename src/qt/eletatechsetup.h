#ifndef ELETATECHSETUP_H
#define ELETATECHSETUP_H

#include "wallet/eletatech.h"

#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class eletatechsetup;
}

class eletatechsetup : public QDialog
{
    Q_OBJECT

public:
    explicit eletatechsetup(QWidget *parent = 0);
    ~eletatechsetup();

private:
    Ui::eletatechsetup *ui;

public Q_SLOTS:
    void reloadEletatechServers();
    void addEletatechServer();
    void removeEletatechServer();
    void getinfoEletatechServer();
    void showButtons(bool show=true);
    void showEletatechIntro();

};

#endif // ELETATECHSETUP_H
