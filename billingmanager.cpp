#include "billingmanager.h"
#include "ui_billingmanager.h"
#include <QtSql>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextBrowser>
#include <QTextFrame>
#include <QTextTableCell>
billingManager::billingManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::billingManager)
{
    ui->setupUi(this);

    QRegExp regExp("[1-9][0-9]*");
    ui->payForm->setValidator(new QRegExpValidator(regExp, this));

    setupview();
}

billingManager::~billingManager()
{
    delete ui;
}
void billingManager::on_okButton_clicked()
{
    this->close();
}
void billingManager::on_roomNo_currentIndexChanged()
{
    updatetable();
}

void billingManager::setupview()
{
    ui->orders->clear();
    ui->payTab->clear();
    ui->roomNo->clear();
    ui->roomNo->addItem(":: select one ::");

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );


    db.setDatabaseName( "./innovativedb.sqlite" );


    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist ( id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT roomno FROM roomlist WHERE occupied <> 0");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        QString roomno = qry.value(0).toString();
        ui->roomNo->addItem(roomno);
    }



}
void billingManager::updatetable()
{

    ui->orders->clear();
    ui->totalBill->setText("0   ");
    ui->orders->setRowCount(0);
    ui->payForm->setEnabled(1);
    ui->payForm->clear();

    QTableWidgetItem * h1 = new QTableWidgetItem("Item");
    QTableWidgetItem * h2 = new QTableWidgetItem("Date");
    QTableWidgetItem * h3 = new QTableWidgetItem("Price");

    ui->orders->setColumnCount(3);
    ui->orders->setHorizontalHeaderItem(0,h1);
    ui->orders->setHorizontalHeaderItem(1,h2);
    ui->orders->setHorizontalHeaderItem(2,h3);


    QTableWidgetItem * h4 = new QTableWidgetItem("Date");
    QTableWidgetItem * h5 = new QTableWidgetItem("Price");

    ui->payTab->setColumnCount(2);
    ui->payTab->setHorizontalHeaderItem(0,h4);
    ui->payTab->setHorizontalHeaderItem(1,h5);

    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->name->setText("-");
        ui->payForm->setEnabled(0);
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
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT occupied FROM roomlist WHERE roomno=:room");
    qry.bindValue(":room",roomno);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    QString guestID = "";
    while(qry.next())
    {
        guestID = qry.value(0).toString();
    }
    qDebug()<<guestID;
    qry.prepare("CREATE TABLE IF NOT EXISTS guestlist ( id INTEGET PRIMARY KEY, name VARCHAR(30),"
                "address VARCHAR(30), nationality VARCHAR(15), phone VARCHAR(15), occupation VARCHAR(15),"
                "purpose VARCHAR(20), occupant INTEGER, room VARCHAR(8), intime VARCHAR(30), outtime VARCHAR(30) )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    qry.prepare("SELECT name,intime FROM guestlist WHERE id=:guestID");
    qry.bindValue(":guestID",guestID);
    if(!qry.exec())
    {
       qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );
    QString intime;
    while (qry.next())
    {
        QString cur_item = qry.value(0).toString();
        ui->name->setText(cur_item);
        intime = qry.value(1).toString();
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS otherorders (id INTEGER PRIMARY KEY, time VARCHAR(30), text VARCHAR(40), price INTEGER, guestid INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );


    qry.prepare("SELECT time,text,price FROM otherorders WHERE guestid = :guestID");
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );
    int totalPrice = 0;
    int r = 0;
    while (qry.next()) {
        QString time = qry.value(0).toString();
        QString text = qry.value(1).toString();
        int price = qry.value(2).toInt();
        totalPrice+=price;

        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * textItem = new QTableWidgetItem(text);
        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->orders->setRowCount(r+1);
        ui->orders->setItem(r,0,textItem);
        ui->orders->setItem(r,1,timeItem);
        ui->orders->setItem(r,2,priceItem);
        r=r+1;
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS restorders (id INTEGET PRIMARY KEY, item VARCHAR(20), quantity INTEGER, price INTEGER, guestID INTEGER, time VARCHAR(20))");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT time,item,price FROM restorders WHERE guestid = :guestID");
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );
    while (qry.next()) {
        QString time = qry.value(0).toString();
        QString text = qry.value(1).toString();
        int price = qry.value(2).toInt();
        qDebug() << time << text << price;
        totalPrice+=price;

        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * textItem = new QTableWidgetItem(text);
        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->orders->setRowCount(r+1);
        ui->orders->setItem(r,0,textItem);
        ui->orders->setItem(r,1,timeItem);
        ui->orders->setItem(r,2,priceItem);
        r=r+1;
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS payments ( id INTEGET PRIMARY KEY, time VARCHAR(25), amount INTEGER, guestID INTEGER )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT time,amount FROM payments WHERE guestID = :guestID");
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    int totalPay = 0;
    r = 0;
    while (qry.next()) {
        QString time = qry.value(0).toString();
        int price = qry.value(1).toInt();
        totalPay+=price;

        qDebug() << time << price;
        QString priceStr;
        priceStr.setNum(price);

        QTableWidgetItem * priceItem = new QTableWidgetItem(priceStr);
        QTableWidgetItem * timeItem = new QTableWidgetItem(time);

        ui->payTab->setRowCount(r+1);
        ui->payTab->setItem(r,0,timeItem);
        ui->payTab->setItem(r,1,priceItem);

        r=r+1;
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT cat FROM roomlist WHERE roomno = :roomno");
    qry.bindValue(":roomno",roomno);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int catID;
    while (qry.next()) {
        catID = qry.value(0).toInt();
    }


    qry.prepare("CREATE TABLE IF NOT EXISTS roomcat (id INTEGET PRIMARY KEY, item VARCHAR(30), price INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Table Created!" );

    qry.prepare("SELECT price FROM roomcat WHERE id = :catID");
    qry.bindValue(":catID",catID);
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
        qDebug( "Table Selected!" );

    int room_rent;
    while(qry.next())
    {
        room_rent = qry.value(0).toInt();
    }

    QDateTime in_time = QDateTime::fromString(intime);
    qDebug()<<"in"<<intime;
    QDateTime cur_time = QDateTime::currentDateTime();
    qDebug()<<"out"<<cur_time.toString();

    int secStayed = in_time.secsTo(cur_time);
    int daysStayed = secStayed/86400;
    if ((secStayed%86400)>600)
    {
        daysStayed++;
    }
    int totalRent = daysStayed*room_rent;
    totalPrice+=totalRent;
    QString totalRentStr;
    totalRentStr.setNum(totalRent);


    QTableWidgetItem * textItem = new QTableWidgetItem("Room Rent");
    QTableWidgetItem * priceItem = new QTableWidgetItem(totalRentStr);
    QTableWidgetItem * timeItem = new QTableWidgetItem(intime);
    int lastRow = ui->orders->rowCount()+1;

    ui->orders->setRowCount(lastRow);
    ui->orders->setItem(lastRow-1,0,textItem);
    ui->orders->setItem(lastRow-1,1,timeItem);
    ui->orders->setItem(lastRow-1,2,priceItem);

    QString TBStr1;
    TBStr1.setNum(totalPrice);
    ui->totalBill->setText(TBStr1);


    QString TBStr2;
    TBStr2.setNum(totalPay);
    ui->totalPay->setText(TBStr2);

    int totalBal = totalPrice - totalPay;
    QString TBStr3;
    TBStr3.setNum(totalBal);
    ui->totalBal->setText(TBStr3);

}

void billingManager::on_payButton_clicked()
{

    QString roomno = ui->roomNo->currentText();
    qDebug() << roomno;

    if(roomno==":: select one ::")
    {
        ui->name->setText("-");
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
    qry.prepare("CREATE TABLE IF NOT EXISTS roomlist (id INTEGET PRIMARY KEY, roomno VARCHAR(5), cat INTEGER, occupied INTEGER)");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    qry.prepare("SELECT occupied FROM roomlist WHERE roomno=:room");
    qry.bindValue(":room",roomno);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    QString guestID = "";
    while(qry.next())
    {
        guestID = qry.value(0).toString();
    }

    qry.prepare("CREATE TABLE IF NOT EXISTS payments ( id INTEGET PRIMARY KEY, time VARCHAR(25), amount INTEGER, guestID INTEGER )");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );




    int id=0;
    qry.prepare("SELECT id FROM payments");
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    while (qry.next()) {
        int cur_item = qry.value(0).toInt();
        if(cur_item > id)
        {
            id=cur_item;
        }
    }
    id++;

    QDateTime QDTime = QDateTime::currentDateTime();
    QString QDTStr = QDTime.toString();
    QString amount = ui->payForm->text();
    ui->payForm->clear();

    qry.prepare("INSERT INTO payments ( id, time, amount, guestID ) VALUES (:id, :time, :amount, :guestid )");
    qry.bindValue(":id",id);
    qry.bindValue(":time",QDTStr);
    qry.bindValue(":amount",amount);
    qry.bindValue(":guestid",guestID);
    if(!qry.exec())
        qDebug() << qry.lastError();
    else
        qDebug( "Room Table Validated..." );

    updatetable();


}
void billingManager::on_payForm_textChanged()
{
    ui->payButton->setEnabled(ui->payForm->hasAcceptableInput());
}

void billingManager::on_print_clicked()
{
    print(ui->payTab,"order");




    QPrinter *p=new QPrinter(QPrinter::HighResolution);

       p->setPaperSize (QPrinter::A4);
       p->setOrientation(QPrinter::Portrait);
       p->setFullPage(true);
       p->setOutputFormat(QPrinter::NativeFormat);
       p->setOutputFileName("/Users/Jaloul/Dropbox/Projet c++/Innovative-Hotel-Manager/test2MonNomDeFichier.pdf");

  // ui->payForm->print(p);
}


void billingManager::print(QTableWidget * tableau_a_imprimer, QString titre)
{
    QPrinter * printer = new QPrinter(QPrinter::HighResolution);
    printer->setPaperSize (QPrinter::A4);
    printer->setOutputFormat (QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    printer->setFullPage(true);
printer->setOutputFileName("/Users/Jaloul/Dropbox/Projet c++/Innovative-Hotel-Manager/test2MonNomDeFichier.pdf");
    QPrintDialog printDialog(printer, this);
    if ( printDialog.exec() == 1)
    {
        QTextBrowser * editor = new QTextBrowser;

        //creation de formats d'écriture
               QTextCharFormat NormalFormat;

        QTextCharFormat ItalicFormat;
        ItalicFormat.setFontItalic(true);

        //On insere la date et l'heure actuelle au début de la premiere page
        QDate date;
        QTime time;
        date = date.currentDate();
        time = time.currentTime();
        QString modif ="\nFait le :\t" + date.toString("dddd dd MMMM yyyy") + " a " + time.toString();

               //changement du format d'ecriture
        editor->setCurrentCharFormat(ItalicFormat);
        editor->setAlignment(Qt::AlignLeft);

               //ajout de notre QString a l'endroit du curseur
        editor->append(modif);

        editor->setCurrentCharFormat(NormalFormat);

        //on insere le titre du tableau
        QTextCharFormat format_gros_titre;
        format_gros_titre.setFontPointSize(20);
        format_gros_titre.setFontWeight(QFont::Bold);
        format_gros_titre.setVerticalAlignment(QTextCharFormat::AlignMiddle);
        format_gros_titre.setUnderlineStyle(QTextCharFormat::SingleUnderline);

        QString title ="\n"+QString::fromUtf8(titre.toStdString().c_str())+"\n";

        editor->setCurrentCharFormat(format_gros_titre);
        editor->setAlignment(Qt::AlignCenter);

        editor->append(title);

        editor->setCurrentCharFormat(NormalFormat);

        //on crée un curseur a l'endroit du curseur actuel
        QTextCursor cursor = editor->textCursor();
        cursor.beginEditBlock();

        //Creation du format du tableau qui sera imprimer
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(Qt::AlignHCenter);
        tableFormat.setAlignment(Qt::AlignLeft);
        tableFormat.setBackground(QColor("#ffffff"));
        tableFormat.setCellPadding(5);
        tableFormat.setCellSpacing(5);

        //Creation du tableau qui sera imprimé avec le nombre de colonne
        //et de ligne que contient le tableau mis en parametre

        QTextTable * tableau = cursor.insertTable(tableau_a_imprimer->rowCount()+1, tableau_a_imprimer->columnCount(), tableFormat);

        QTextFrame *frame = cursor.currentFrame();
        QTextFrameFormat frameFormat = frame->frameFormat();
        frameFormat.setBorder(0);
        frame->setFrameFormat(frameFormat);

        //Format des HEADER du tableau
        QTextCharFormat format_entete_tableau;
        format_entete_tableau.setFontPointSize(15);
        format_entete_tableau.setFontWeight(QFont::Bold);

        //Format du texte des cellules du tableau
        QTextCharFormat format_cellule;
        format_cellule.setFontPointSize(12);

        //on ecrit les HEADERS du tableaux dans le tableau a imprimer
        for ( int i = 0 ; i < tableau_a_imprimer->columnCount() ; i++ )
        {
            //on selectionne la premiere cellule de chaque colonne
            QTextTableCell titre = tableau->cellAt(0,i);

            //on place le curseur a cet endroit
            QTextCursor cellCursor = titre.firstCursorPosition();

            //on écrit dans la cellule
            cellCursor.insertText(tableau_a_imprimer->horizontalHeaderItem(i)->text(),format_entete_tableau);
        }

        QTextTableCell cell;
        QTextCursor cellCursor;

        for (int row = 1; row < tableau->rows(); row ++)
            for (int col = 0; col < tableau->columns(); col ++)
            {
                cell = tableau->cellAt(row,col);
                cellCursor = cell.firstCursorPosition();

                cellCursor.insertText(tr("%1").arg(tableau_a_imprimer->item(row-1,col)->text()),format_cellule);
            }

        //fin de l'edition
               cursor.endEditBlock();

               //impression de notre editor dans le QPrinter initialisé au début de la fonction
        editor->print(printer);
    }
}
