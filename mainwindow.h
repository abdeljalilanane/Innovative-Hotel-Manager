#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class mainWindow;
}
class roomsPerCat;
class checkInForm;
class checkOutForm;
class addRestaurantOrder;
class addOtherOrders;
class editRoomCat;
class editRoom;
class editRestaurant;
class billingManager;
class setting;
class AjouterReservation;
class ListeReserv;
class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    void setupview();

private:
    Ui::mainWindow *ui;
    roomsPerCat *InnOrpc;
    checkInForm *InnOcif;
    checkOutForm *InnOcof;
    addRestaurantOrder *InnOaro;
    addOtherOrders *InnOaoo;
    editRoomCat *InnOerc;
    editRoom *InnOeroom;
    editRestaurant *InnOerest;
    billingManager *InnObill;
    setting *InnOset;
    AjouterReservation *InnAjRes;
    ListeReserv *InnLIRes;


private slots:
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();
    void on_button10_clicked();
    void setupviewS();
    //void on_commandLinkButton_2_clicked();
    void on_BtnAjouterReservation_clicked();
    void on_BtnListeReservation_clicked();
};

#endif // MAINWINDOW_H
