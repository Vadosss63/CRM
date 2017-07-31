QT += core sql
QT -= gui

CONFIG += c++11

TARGET = SQLServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sqlmodule.cpp \
    ../Data/data.cpp

HEADERS += \
    sqlmodule.h \
    ../Data/data.h
