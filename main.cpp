#include <QtGui/QApplication>
#include "mainwindow.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //login
    mainWindow l;
    l.show();
    return a.exec();
}
