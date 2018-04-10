#include "eletatechinit.h"
#include "ui_eletatechinit.h"
#include "net.h"
#include "util.h"
#include "skinize.h"

#include <string>
#include <iostream>

#include <QStringList>
#include <QUrl>

EltTechInit::EltTechInit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EltTechInit)
{
    ui->setupUi(this);
}

EltTechInit::~EltTechInit()
{
    delete ui;
}

void EltTechInit::ShowEletatechIntro(bool exitAfter)
{
    EltTechInit eletatechinit;
    eletatechinit.setWindowIcon(QIcon(":icons/eletacoin"));
    eletatechinit.setStyleSheet(Skinize());

    if(!eletatechinit.exec())
    {
        if(exitAfter)
            exit(0);
        else
            return;
    }

    QString ServersToAdd = eletatechinit.GetServers();
    QStringList ss = ServersToAdd.split('\n');

    for (int i = 0; i < ss.size(); ++i){
        QString Server = ss.at(i);
        QString strippedServer = Server.remove(' ');
        if(strippedServer != "")
        {
            WriteConfigFile("addanonserver",strippedServer.toStdString());
        }
    }
}

QString EltTechInit::GetServers()
{
    return ui->plainTextEdit->toPlainText();
}
