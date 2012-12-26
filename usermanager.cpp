#include "usermanager.h"
#include "ui_usermanager.h"
#include <QDebug>
#include <QtSql>
#include <QTableWidget>

userManager::userManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userManager)
{
    ui->setupUi(this);
    setupview();
}

userManager::~userManager()
{
    delete ui;
}

void userManager::setupview()
{
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

   int i=0;

    QSqlQuery req;
    req.prepare("SELECT * FROM agent");
        if( !req.exec() )
        {

            qDebug() << qry.lastError();
        }
        else
        { qDebug("done1");

            ui->agentlist->setRowCount(2);
            while(req.next())//pour avancer les lignes
            {
                ui->agentlist->setRowCount(i+1);

               QString user=req.value(0).toString();
               QString pass=req.value(1).toString();


               ui->agentlist->setItem(i,0,new QTableWidgetItem(user));
               ui->agentlist->setItem(i,1,new QTableWidgetItem(pass));

               i++;
        }

        }

}

void userManager::on_ajout_clicked()
{
    QSqlQuery qry;

    int j=0;

    if(!qry.exec("SELECT * FROM agent"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );



    while (qry.next()) {
        QString user = qry.value(0).toString();
        QString pass = qry.value(1).toString();

        ui->agentlist->setItem(j,0,new QTableWidgetItem(user));
        ui->agentlist->setItem(j,1,new QTableWidgetItem(pass));

        qDebug() << user,pass;
        j++;

    }
}












