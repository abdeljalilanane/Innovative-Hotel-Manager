#ifndef BILLINGMANAGER_H
#define BILLINGMANAGER_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
    class billingManager;
}
class billingManager : public QDialog
{
    Q_OBJECT

public:
    explicit billingManager(QWidget *parent = 0);
    ~billingManager();
    void setupview();
    void updatetable();
    void print(QTableWidget * tableau_a_imprimer, QString titre);
private:
    Ui::billingManager *ui;

private slots:
    void on_okButton_clicked();
    void on_roomNo_currentIndexChanged();
    void on_payButton_clicked();
    void on_payForm_textChanged();
    void on_print_clicked();
};

#endif // BILLINGMANAGER_H
