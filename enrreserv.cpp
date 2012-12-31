#include "enrreserv.h"
#include "ui_enrreserv.h"

EnrReserv::EnrReserv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnrReserv)
{
    ui->setupUi(this);
}

EnrReserv::~EnrReserv()
{
    delete ui;
}
