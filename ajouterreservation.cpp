#include "ajouterreservation.h"
#include "ui_ajouterreservation.h"
#include <QtSql>
#include <QDebug>
#include <QDateTime>

AjouterReservation::AjouterReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterReservation)
{
    ui->setupUi(this);
    QRegExp regExp1("[A-Za-z][A-Za-z ]*[A-Za-z0-9]*");
    ui->nameText->setValidator(new QRegExpValidator(regExp1, this));

    QRegExp regExp2("[0-9][0-9]*[0-9]*");
    ui->phone->setValidator(new QRegExpValidator(regExp2, this));


            QRegExp regExp3("[0-9]{8,8}");
            ui->CINText->setValidator(new QRegExpValidator(regExp3, this));
    setupview();
}

void AjouterReservation::setupview()
{
    QDate QDTime = QDate::currentDate();
    ui->dateEditArive->setDate(QDTime);
    QDate QDTime2 = QDate::currentDate();
    ui->dateEditDepart->setDate(QDTime2.addDays(1));
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGER PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );

    int j=0;

    if(!qry.exec("SELECT item FROM roomcat"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    ui->catList->clear();
    ui->catList->addItem(":: select one ::");

    while (qry.next()) {
        QString item = qry.value(0).toString();

        ui->catList->addItem(item);

        qDebug() << item;
        j++;

    }
}

AjouterReservation::~AjouterReservation()
{
    delete ui;
}

void AjouterReservation::on_okButton_clicked()
{
    QString name = ui->nameText->text();
    QString cin = ui->CINText->text();

    QString phone = ui->phone->text();



    QString cat = ui->catList->currentText();
    QString room = ui->roomList->currentText();

    //QDateTime QDTime = QDateTime::currentDateTime();
    QString QDTStr = ui->dateEditArive->date().toString();
    QString QDTStr2 = ui->dateEditDepart->date().toString();

    int id=0;

    qDebug() << name << cin << phone  << cat << room;

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
      qDebug() << qry.lastError();
    else
      qDebug( "Table Created!" );


    qry.prepare("SELECT price FROM roomcat WHERE item=:cat");
    qry.bindValue(":cat",cat);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    int price = 0;
    while (qry.next()) {
       price = qry.value(0).toInt();
    }
    qDebug() << price;

    qry.prepare("CREATE TABLE IF NOT EXISTS resvlist ( id INTEGET PRIMARY KEY AUTO_INCREMENT, name VARCHAR(30),cin VARCHAR(8), phone VARCHAR(15), room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    if(!qry.exec("SELECT id FROM resvlist"))
    {
       qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );
    while (qry.next()) {
        int cur_item = qry.value(0).toInt();
        if(cur_item > id)
        {
            id=cur_item;
          }
    }
    id++;

  qry.prepare("INSERT INTO resvlist (id,name,cin,phone,room,intime, outtime) VALUES (:id,:name,:cin,:phone,:room,:time,:time2)");
    qry.bindValue(":id",id);
  qry.bindValue(":name",name);
  qry.bindValue(":cin",cin);
  qry.bindValue(":phone",phone);
  qry.bindValue(":room",room);
  qry.bindValue(":time",QDTStr);
  qry.bindValue(":time2",QDTStr2);
  if(!qry.exec())
       qDebug() << qry.lastError();
  else
       qDebug( "Table Created!" );


  qry.prepare("UPDATE roomlist SET occupied=:id WHERE roomno=:room");
  qry.bindValue(":id",id);
  qry.bindValue(":room",room);
  if(!qry.exec())
       qDebug() << qry.lastError();
  else
       qDebug( "updated!" );

    this->close();

}

void AjouterReservation::on_catList_currentIndexChanged(const QString &arg1)
{
    ui->roomList->clear();
    QString nameStr= ui->catList->currentText();

    if(nameStr==":: select one ::")
    {
        ui->roomList->setEnabled(0);
        ui->okButton->setEnabled(0);
        return;
    }


    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );


    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );


    qry.prepare("SELECT id FROM roomcat WHERE item = :name");
    qry.bindValue(":name",nameStr);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int i=0;
    while (qry.next()) {
        i = qry.value(0).toInt();
    }


    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT roomno FROM roomlist WHERE cat = :item AND occupied = 0");
    qry.bindValue(":item",i);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        QString roomno = qry.value(0).toString();
        ui->roomList->addItem(roomno);
        ui->roomList->setEnabled(1);
    }
}

void AjouterReservation::on_roomList_currentIndexChanged(int index)
{
    ui->okButton->setEnabled((ui->nameText->hasAcceptableInput())&&(ui->phone->hasAcceptableInput())&&(ui->CINText->hasAcceptableInput()));

}

void AjouterReservation::on_dateEditArive_dateChanged()
{

    ui->dateEditDepart->setDate(ui->dateEditArive->date().addDays(1));
}
