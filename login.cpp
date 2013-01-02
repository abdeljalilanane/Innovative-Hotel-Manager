#include <QtSql>
#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "usermanager.h"
QString loginT;
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
QString login::getNom(){
    return loginT;
}

void login::on_ok_clik()
{
    loginT = ui->loginT->text();
    QString passwordT = ui->passwordT->text();


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
      {qDebug( "Table Created!" );

        qry.prepare("INSERT INTO agent (id,user,pass) VALUES (:id,:user,:pass)");
        qry.bindValue(":id",1);
        qry.bindValue(":user","root");
        qry.bindValue(":pass","root");

        if(!qry.exec())
             qDebug() << qry.lastError();
        else
             qDebug( "root root!" );
    }
    QSqlQuery req;
    QString user="";
    QString pass="";
    req.prepare("SELECT * FROM agent where user = :user and pass = :pass");
    req.bindValue(":user",loginT);
    req.bindValue(":pass",passwordT);
        if( !req.exec() )
        {

            qDebug() << qry.lastError();

        }
        else
        { qDebug("select agent login");

            while(req.next())//pour avancer les lignes
            {
                user=req.value(1).toString();
                pass=req.value(2).toString();


             }
        }


    if ((loginT==user)&&(passwordT==pass))
    {
        ui->l->clear();
        ui->p->clear();
        if(user=="root")
        {
            userManager *u=new userManager;
            u->show();
            this->setVisible(false);
        }
        else
        {
            mainWindow * u=new mainWindow;
            u->show();
            this->setVisible(false);
        }

     }
    else
    {
        ui->l->setText("login introuvable");
        ui->p->setText("passe introuvable");

    }




}


