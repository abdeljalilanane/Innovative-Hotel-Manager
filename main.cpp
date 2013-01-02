#include <QtGui/QApplication>
#include "mainwindow.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login l;
   // mainWindow l;
    l.show();
    return a.exec();
}
