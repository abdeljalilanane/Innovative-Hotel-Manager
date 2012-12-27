#include "usermanager.h"
#include "ui_usermanager.h"
#include <QDebug>
#include <QtSql>
#include <QTableWidget>
#include <QMessageBox>

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
         ui->agentlist->setRowCount(ui->agentlist->rowCount()+1);

}

void userManager::on_ajout_clicked()
{
    int r= ui->agentlist->currentRow();
    QSqlQuery qry;
    QTableWidgetItem *user = ui->agentlist->item(r,0);
    QString user1= user->text();
    QTableWidgetItem *pass = ui->agentlist->item(r,1);
    QString pass1= pass->text();
    r=r+1;
    switch( QMessageBox::warning(this,"Confirmation","Voulez-vous vraiment ajouter ce personnel ? ","Oui","Non",0,1))
    {
    case 0:
        qry.prepare("INSERT INTO agent (user,pass) VALUES (:user,:pass)");

        qry.bindValue(":user",user1);
        qry.bindValue(":pass",pass1);

    if (qry.exec())
    { ///Requete reussi
    qDebug("req reussi! ");
    QMessageBox::information(this, tr("Done"),tr("Le utilisateur ajouter avec succes! "));
setupview();
    }
    else
    {
        qDebug("req NO reussi! ");
        QMessageBox::information(this, tr("Done"),tr("errue ajouter utilisateur! "));

    }

    case 1:
    default:
    ;
    }

}

void userManager::on_supprimer_clicked()
{
    int r= ui->agentlist->currentRow();
    QSqlQuery req ;
    QTableWidgetItem *z = ui->agentlist->item(r,0);
    QString zs= z->text();
    switch( QMessageBox::warning(this,"Confirmation","Voulez-vous vraiment supprimer ce personnel ? ","Oui","Non",0,1))
    {
    case 0:
    req.prepare("delete from agent where user='"+zs+"'");
    if (req.exec())
    { ///Requete reussi
    qDebug("req reussi! ");
    QMessageBox::information(this, tr("Done"),tr("Le utilisateur supprime avec succes! "));
    ui->agentlist->removeRow(r);
    }

    case 1:
    default:
    ;
    }
}
