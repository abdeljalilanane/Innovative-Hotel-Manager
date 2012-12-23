#include "ajouterreservation.h"
#include "ui_ajouterreservation.h"

AjouterReservation::AjouterReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterReservation)
{
    ui->setupUi(this);
}

AjouterReservation::~AjouterReservation()
{
    delete ui;
}
