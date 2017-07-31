QT += core
QT -= gui

CONFIG += c++11

TARGET = Network
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

unix:!macx: LIBS += -lboost_system
unix:!macx: LIBS += -ltbb
unix:!macx: LIBS += -lpthread


SOURCES += main.cpp \
    network.cpp

DISTFILES += \
    Network.pro.user

HEADERS += \
    network.h
