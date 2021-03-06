
QT       += core gui
QT       += sql

TARGET = innovative
TEMPLATE = app
CONFIG += x86_64

SOURCES += main.cpp\
        mainwindow.cpp \
    roomspercat.cpp \
    editroomcat.cpp \
    editroom.cpp \
    editrestaurant.cpp \
    editaddrestaurant.cpp \
    addrestaurantorder.cpp \
    addotherorders.cpp \
    billingmanager.cpp \
    checkoutform.cpp \
    editremrestaurant.cpp \
    editaddroomcat.cpp \
    checkinform.cpp \
    setting.cpp \
    ajouterreservation.cpp \
    login.cpp \
    usermanager.cpp \
    listereserv.cpp

HEADERS  += mainwindow.h \
    roomspercat.h \
    editroomcat.h \
    editroom.h \
    editrestaurant.h \
    editaddrestaurant.h \
    addrestaurantorder.h \
    addotherorders.h \
    billingmanager.h \
    checkoutform.h \
    editremrestaurant.h \
    editaddroomcat.h \
    checkinform.h \
    setting.h \
    ajouterreservation.h \
    login.h \
    usermanager.h \
    listereserv.h

FORMS    += mainwindow.ui \
    roomspercat.ui \
    editroomcat.ui \
    editroom.ui \
    editrestaurant.ui \
    editaddrestaurant.ui \
    addrestaurantorder.ui \
    addotherorders.ui \
    billingmanager.ui \
    checkoutform.ui \
    editremrestaurant.ui \
    editaddroomcat.ui \
    checkinform.ui \
    setting.ui \
    dialog.ui \
    ajouterreservation.ui \
    login.ui \
    usermanager.ui \
    listereserv.ui

RESOURCES += \
    images.qrc

OTHER_FILES +=
