#include "checkinform.h"
#include "ui_checkinform.h"
#include <QtSql>
#include <QDebug>
#include <QDateTime>
#include <QCompleter>

checkInForm::checkInForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkInForm)
{
    ui->setupUi(this);

    QRegExp regExp1("[A-Za-z][A-Za-z ]*[A-Za-z0-9]*");
    ui->nameText->setValidator(new QRegExpValidator(regExp1, this));

    QRegExp regExp2("[1-9][0-9]*[0-9]*");
    ui->phone->setValidator(new QRegExpValidator(regExp2, this));

    QRegExp regExp3("[A-Za-z0-9][A-Za-z0-9, ]*[A-Za-z0-9 ]*");
    ui->addText->setValidator(new QRegExpValidator(regExp3, this));

    setupview();




}

checkInForm::~checkInForm()
{
    delete ui;
}

void checkInForm::setupview()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );



     QSqlQuery qry1;
     if(!qry1.exec("SELECT cin FROM `resvlist`"))
     {
         qDebug() << qry1.lastError();
     }
     else
         qDebug( "Table Selected!" );
     QStringList wordList;


     while (qry1.next()) {
         QString item = qry1.value(0).toString();
        wordList << item;


         qDebug() << wordList;


     }



      //QLineEdit *lineEdit = new QLineEdit(this);

      QCompleter *completer = new QCompleter(wordList, this);
      completer->setCaseSensitivity(Qt::CaseInsensitive);
      ui->LinCIN->setCompleter(completer);


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

void checkInForm::on_catList_currentIndexChanged()
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

void checkInForm::on_okButton_clicked()
{

    QString name = ui->nameText->text();
    QString address = ui->addText->text();
    QString nationality = ui->nationality->currentText();
    QString phone = ui->phone->text();
    QString occupation = ui->occupation->currentText();
    QString purpose = ui->purpose->currentText();

    int occupant = ui->occupant->value();
    QString cat = ui->catList->currentText();
    QString room = ui->roomList->currentText();

    QDateTime QDTime = QDateTime::currentDateTime();
    QString QDTStr = QDTime.toString();

    int id=0;

    qDebug() << name << address << nationality << phone << occupation << purpose << occupant << cat << room;

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

    qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    if(!qry.exec("SELECT id FROM guestlist"))
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

  qry.prepare("INSERT INTO guestlist (id,name,address,nationality,phone,occupation,purpose,occupant,room,intime, outtime) VALUES (:id,:name,:address,:nationality,:phone,:occupation,:purpose,:occupant,:room,:time,'0')");
  qry.bindValue(":id",id);
  qry.bindValue(":name",name);
  qry.bindValue(":address",address);
  qry.bindValue(":nationality",nationality);
  qry.bindValue(":phone",phone);
  qry.bindValue(":occupation",occupation);
  qry.bindValue(":purpose",purpose);
  qry.bindValue(":occupant",occupant);
  qry.bindValue(":room",room);
  qry.bindValue(":time",QDTStr);
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


void checkInForm::on_roomList_currentIndexChanged()
{
    ui->okButton->setEnabled((ui->nameText->hasAcceptableInput())&&(ui->phone->hasAcceptableInput())&&(ui->addText->hasAcceptableInput()));
}


void checkInForm::on_LinCIN_returnPressed()
{
    QString Name;
    QString cin;
    QString phone;
    QString cat;
    QString NoChom;
    QString data;
    QString datfep;

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );


    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM `resvlist` where cin='"+ui->LinCIN->text()+"'"))
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    while (qry.next()) {
        Name=qry.value(1).toString();
        cin=qry.value(2).toString();
        phone=qry.value(3).toString();
        NoChom=qry.value(4).toString();
        data=qry.value(5).toString();
        datfep=qry.value(6).toString();



    }
    ui->nameText->setText(Name);
    ui->phone->setText(phone);
    ui->roomList->clear();
    ui->roomList->addItem(NoChom);
    ui->catList->setEnabled(0);
    /*ui->->setText();
    ui->->setText();
    ui->->setText();*/



}

void checkInForm::on_occupant_editingFinished()
{
    ui->okButton->setEnabled((ui->nameText->hasAcceptableInput())&&(ui->phone->hasAcceptableInput())&&(ui->addText->hasAcceptableInput()));

}
