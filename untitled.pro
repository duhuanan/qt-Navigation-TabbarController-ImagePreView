#-------------------------------------------------
#
# Project created by QtCreator 2020-12-31T06:54:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qimagepreview.cpp \
    qanimationstackedwidget.cpp \
    qimagepreviewview.cpp \
    qfiledownloadmanager.cpp \
    qnavigation.cpp \
    qtabbarwidget.cpp

HEADERS  += mainwindow.h \
    qlog.h \
    qglobaldefine.h \
    qimagepreview.h \
    qanimationstackedwidget.h \
    qimagepreviewview.h \
    qfiledownloadmanager.h \
    qnavigation.h \
    qtabbarwidget.h

FORMS    += mainwindow.ui
