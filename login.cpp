#include <QtSql>
#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "usermanager.h"

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

/*
    //conex DB
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS agent (id INTEGER PRIMARY KEY, user VARCHAR(30), pass VARCHAR(30))");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

*/
    if ((login=="root")&&(pass=="pass"))
    {
        //mainWindow *w=new mainWindow;
        //w->show();

        userManager *u=new userManager;
        u->show();
        this->setVisible(false);
     }



}


