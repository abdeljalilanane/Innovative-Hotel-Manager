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
    
private:
    Ui::ListeReserv *ui;
};

#endif // LISTERESERV_H
