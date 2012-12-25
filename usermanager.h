#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>

namespace Ui {
class userManager;
}

class userManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit userManager(QWidget *parent = 0);
    void setupview();
    ~userManager();
    
private slots:


private:
    Ui::userManager *ui;
};

#endif // USERMANAGER_H
