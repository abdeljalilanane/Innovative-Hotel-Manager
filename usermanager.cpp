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


   int i=0;

    QSqlQuery req;
    req.prepare("SELECT * FROM agent");
        if( !req.exec() )
        {

            //qDebug() << qry.lastError();
        }
        else
        { qDebug("liste agent trouve");

            ui->agentlist->setRowCount(0);
            while(req.next())//pour avancer les lignes
            {
                 ui->agentlist->setRowCount(i+1);

               QString user=req.value(1).toString();
               QString pass=req.value(2).toString();


               ui->agentlist->setItem(i,0,new QTableWidgetItem(user));
               ui->agentlist->setItem(i,1,new QTableWidgetItem(pass));

               i++;
        }

        }

}

void userManager::on_ajout_clicked()
{
    ui->agentlist->setRowCount(ui->agentlist->rowCount()+1);
}
