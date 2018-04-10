#include "eletatechsetup.h"
#include "eletatechitem.h"
#include "ui_eletatechsetup.h"
#include "net.h"
#include "skinize.h"
#include "util.h"

#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <QtNetwork>
#include <QWidget>

eletatechsetup::eletatechsetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eletatechsetup)
{
    ui->setupUi(this);
    ui->getInfoButton->setVisible(false);
    ui->removeButton->setVisible(false);

    ui->saveButton->setVisible(false);

    this->setWindowTitle("Eletatech");

    connect(ui->addNewButton,SIGNAL(clicked()),this,SLOT(addEletatechServer()));
    connect(ui->getInfoButton,SIGNAL(clicked()),this,SLOT(getinfoEletatechServer()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeEletatechServer()));
    connect(ui->serversListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showButtons()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(close()));

    reloadEletatechServers();
}

eletatechsetup::~eletatechsetup()
{
    delete ui;
}

void eletatechsetup::addEletatechServer()
{
    QString serverToAdd = ui->addServerText->text();

    if(serverToAdd == "")
        return;

    serverToAdd = serverToAdd.remove(' ').remove('\n').remove('\r').remove('\t');

    LOCK(cs_vAddedAnonServers);
    std::vector<std::string>::iterator it = vAddedAnonServers.begin();
    for(; it != vAddedAnonServers.end(); it++)
        if (serverToAdd.toStdString() == *it)
            break;

    WriteConfigFile("addanonserver", serverToAdd.toStdString());
    if (it == vAddedAnonServers.end())
        vAddedAnonServers.push_back(serverToAdd.toStdString());

    ui->addServerText->clear();

    reloadEletatechServers();
}

void eletatechsetup::reloadEletatechServers()
{
    ui->serversListWidget->clear();

    const std::vector<std::string>& confAnonServers = mapMultiArgs["-addanonserver"];

    BOOST_FOREACH(std::string confAnonServer, confAnonServers) {
        ui->serversListWidget->addItem(QString::fromStdString(confAnonServer));
    }

    BOOST_FOREACH(std::string vAddedAnonServer, vAddedAnonServers) {
        ui->serversListWidget->addItem(QString::fromStdString(vAddedAnonServer));
    }
}

void eletatechsetup::showEletatechIntro()
{
/*
    setWindowIcon(QIcon(":icons/eletacoin"));
    setStyleSheet(Skinize());

    ui->saveButton->setVisible(true);

    exec();
*/
}

void eletatechsetup::removeEletatechServer()
{
    QString serverToRemove = ui->serversListWidget->currentItem()->text();

    if(serverToRemove == "")
        return;

    QMessageBox::StandardButton btnRetVal = QMessageBox::question(this, tr("Remove Eletatech server"),
        tr("You are about to remove the following Eletatech server: ") + "<br><br>" + serverToRemove + "<br><br>" + tr("Are you sure?"),
        QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);

    if(btnRetVal == QMessageBox::Cancel)
        return;

    LOCK(cs_vAddedAnonServers);
    std::vector<std::string>::iterator it = vAddedAnonServers.begin();

    RemoveConfigFile("addanonserver", serverToRemove.toStdString());
    for(; it != vAddedAnonServers.end(); it++)
        if (serverToRemove == QString::fromStdString(*it))
            break;

    if (it != vAddedAnonServers.end())
    {
      vAddedAnonServers.erase(it);
      QMessageBox::critical(this, windowTitle(),
          tr("Removed."),
          QMessageBox::Ok, QMessageBox::Ok);
    }

    showButtons(false);
    reloadEletatechServers();
}

void eletatechsetup::showButtons(bool show)
{
    ui->getInfoButton->setVisible(show);
    ui->removeButton->setVisible(show);
}

void eletatechsetup::getinfoEletatechServer()
{
    QString serverToCheck = ui->serversListWidget->currentItem()->text();

    if(serverToCheck == "")
        return;

    QStringList server = serverToCheck.split(':');

    if(server.length() != 2)
        return;

    try {
        Eletatech *eletatech = new Eletatech();
        UniValue data = eletatech->GetServerInfo(serverToCheck.toStdString());

        QMessageBox::information(this, windowTitle(),
            tr("Eletatech server") + "<br><br>" +  tr("Address: ") + serverToCheck + "<br>" + tr("Min amount: ") + QString::number(data["min_amount"].get_real()) + " <br>" + tr("Max amount: ") + QString::number(data["max_amount"].get_real()) + "<br>" + tr("Tx fee: ") + QString::number(data["transaction_fee"].get_real()) + "%",
            QMessageBox::Ok, QMessageBox::Ok);
    }
    catch(const std::runtime_error &e)
    {
        QMessageBox::warning(this, tr("Eletatech server"),
                             "<qt>Could not get info:<br/><br/>" +
                             tr(e.what())+"</qt>");
    }
}
