#include "eletatechitem.h"
#include "ui_eletatechitem.h"

eletatechitem::eletatechitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eletatechitem),
    host(""),
    name("")
{
    ui->setupUi(this);
}

void eletatechitem::setHost(QString hostStr)
{
    host = hostStr;
    ui->serverHostLabel->setText(hostStr);
}

void eletatechitem::setName(QString nameStr)
{
    name = nameStr;
    ui->serverNameLabel->setText(nameStr);
}

eletatechitem::~eletatechitem()
{
    delete ui;
}
