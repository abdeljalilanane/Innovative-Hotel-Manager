#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    QString getNom();
    ~login();
    
private:
    Ui::login *ui;

private slots:
    void on_ok_clik();

};

#endif // LOGIN_H
