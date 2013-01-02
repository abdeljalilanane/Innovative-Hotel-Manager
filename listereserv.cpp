#include "listereserv.h"
#include "ui_listereserv.h"
#include "ajouterreservation.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QTableWidget>

ListeReserv::ListeReserv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListeReserv)
{
    ui->setupUi(this);
    //setupview();
   ListeReservation();
}

ListeReserv::~ListeReserv()
{
    delete ui;
}

void ListeReserv::ListeReservation()

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
ui->catList->setColumnCount(7);
        QSqlQuery req;
        req.prepare("SELECT * FROM resvlist");
            if( !req.exec() )
            {

                QMessageBox::critical(0, qApp->tr("Cannot open database"),
                    qApp->tr("impossible de passer la requete.\n Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            { qDebug("done1");

               // ui->catList->setRowCount(0);
                while(req.next())//pour avancer les lignes
                {
                    ui->catList->setRowCount(i+1);

                   QString ID=req.value(0).toString();
                   QString NAME=req.value(1).toString();
                   QString CIN=req.value(2).toString();
                   QString PHONE=req.value(3).toString();
                   QString ROOM=req.value(4).toString();
                   QString INTIME=req.value(5).toString();
                   QString OUTTIME=req.value(6).toString();
                   qDebug("done2");

                   ui->catList->setItem(i,0,new QTableWidgetItem(ID));
                   ui->catList->setItem(i,1,new QTableWidgetItem(NAME));
                   ui->catList->setItem(i,2,new QTableWidgetItem(CIN));
                   ui->catList->setItem(i,3,new QTableWidgetItem(PHONE));
                   ui->catList->setItem(i,4,new QTableWidgetItem(ROOM));
                   ui->catList->setItem(i,5,new QTableWidgetItem(INTIME));
                   ui->catList->setItem(i,6,new QTableWidgetItem(OUTTIME));
                   i++;
            }



            }


}

void ListeReserv::on_okButton_clicked()
{
    this->close();
}

void ListeReserv::on_addCat_clicked()
{
    AjouterReservation *u=new AjouterReservation();
    u->show();
    this->close();
}
