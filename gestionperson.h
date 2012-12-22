#ifndef GESTIONPERSON_H
#define GESTIONPERSON_H

#include <QMainWindow>

namespace Ui {
class GestionPerson;
}

class GestionPerson : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GestionPerson(QWidget *parent = 0);
    ~GestionPerson();
    
private:
    Ui::GestionPerson *ui;
};

#endif // GESTIONPERSON_H
