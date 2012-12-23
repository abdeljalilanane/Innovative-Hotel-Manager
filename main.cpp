#include <QtGui/QApplication>
#include "mainwindow.h"
#include"gestionperson.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    //GestionPerson w;

    w.show();

    return a.exec();
}
