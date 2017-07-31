#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T09:24:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Table
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabledata.cpp \
    ../Data/data.cpp

HEADERS  += mainwindow.h \
    tabledata.h \
    ../Data/data.h

FORMS    += mainwindow.ui
