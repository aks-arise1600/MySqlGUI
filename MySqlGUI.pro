#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T15:30:41
#
#-------------------------------------------------

QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySqlGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mysqllogin.cpp \
    sqlquery.cpp \
    dialogselectdb.cpp \
    dialoguploadsql.cpp \
    insertvalue.cpp \
    insertlineform.cpp

HEADERS += \
        mysqllogin.h \
    sqlquery.h \
    dialogselectdb.h \
    dialoguploadsql.h \
    insertvalue.h \
    common.h \
    insertlineform.h

FORMS += \
        mysqllogin.ui \
    sqlquery.ui \
    dialogselectdb.ui \
    dialoguploadsql.ui \
    insertvalue.ui \
    insertlineform.ui
RESOURCES += \
    icons.qrc
