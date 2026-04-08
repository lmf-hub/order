#-------------------------------------------------
#
# Project created by QtCreator 2025-06-21T14:54:47
#
#-------------------------------------------------

QT       += core gui
QT += core gui sql
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = order0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        customer.cpp \
        dish.cpp \
        main.cpp \
        mainwindow.cpp \
        orderdetail.cpp \
        orderdish.cpp \
        orders.cpp \
        payment.cpp \
        project.cpp \
        queue.cpp \
        revenue.cpp \
        tables.cpp \
        top_dish.cpp

HEADERS += \
        customer.h \
        dish.h \
        mainwindow.h \
        orderdetail.h \
        orderdish.h \
        orders.h \
        payment.h \
        project.h \
        queue.h \
        revenue.h \
        tables.h \
        top_dish.h

FORMS += \
        customer.ui \
        dish.ui \
        mainwindow.ui \
        orderdetail.ui \
        orderdish.ui \
        orders.ui \
        payment.ui \
        project.ui \
        queue.ui \
        revenue.ui \
        tables.ui \
        top_dish.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
