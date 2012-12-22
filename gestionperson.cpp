#include "gestionperson.h"
#include "ui_gestionperson.h"

GestionPerson::GestionPerson(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionPerson)
{
    ui->setupUi(this);
}

GestionPerson::~GestionPerson()
{
    delete ui;
}
