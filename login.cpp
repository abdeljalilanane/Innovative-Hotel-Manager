#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(ui->B_ok,SIGNAL(clicked()),this, SLOT(on_ok_clik()));
    ui->passwordT->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

void login::on_ok_clik()
{
    QString login = ui->loginT->text();
    QString pass = ui->passwordT->text();

    if ((login=="root")&&(pass=="pass"))
    {
        mainWindow *w=new mainWindow;
        w->show();
        this->setVisible(false);
     }


}


