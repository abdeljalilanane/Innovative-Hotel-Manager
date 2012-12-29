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
    void setupview();
    
private slots:
    void on_okButton_clicked();

    void on_catList_currentIndexChanged(const QString &arg1);

    void on_roomList_currentIndexChanged(int index);

private:
    Ui::AjouterReservation *ui;
};

#endif // AJOUTERRESERVATION_H
