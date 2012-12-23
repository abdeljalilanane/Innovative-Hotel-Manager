#ifndef AJOUTERRESERVATION_H
#define AJOUTERRESERVATION_H

#include <QDialog>

namespace Ui {
class AjouterReservation;
}

class AjouterReservation : public QDialog
{
    Q_OBJECT
    
public:
    explicit AjouterReservation(QWidget *parent = 0);
    ~AjouterReservation();
    
private:
    Ui::AjouterReservation *ui;
};

#endif // AJOUTERRESERVATION_H
