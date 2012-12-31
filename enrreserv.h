#ifndef ENRRESERV_H
#define ENRRESERV_H

#include <QDialog>

namespace Ui {
class EnrReserv;
}

class EnrReserv : public QDialog
{
    Q_OBJECT
    
public:
    explicit EnrReserv(QWidget *parent = 0);
    ~EnrReserv();
    
private:
    Ui::EnrReserv *ui;
};

#endif // ENRRESERV_H
