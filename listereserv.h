#ifndef LISTERESERV_H
#define LISTERESERV_H

#include <QDialog>

namespace Ui {
class ListeReserv;
}

class ListeReserv : public QDialog
{
    Q_OBJECT
    
public:
    explicit ListeReserv(QWidget *parent = 0);
    void setupview();
    void ListeReservation();
    ~ListeReserv();
    
private slots:
    void on_okButton_clicked();

    void on_addCat_clicked();

    void on_catList_clicked();

    void on_rmCat_clicked();

private:
    Ui::ListeReserv *ui;
};

#endif // LISTERESERV_H
