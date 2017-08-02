QT += core
QT -= gui

CONFIG += c++11

TARGET = Network
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lpthread


SOURCES += main.cpp \
    network.cpp

HEADERS += \
    network.h


LIBS += "-LC:/boost/boost_mingw_4_9/lib" \
            -libboost_system-mgw49-mt-1_64


INCLUDEPATH += $$PWD/../../../../../../boost/boost_mingw_4_9/include/boost-1_64
DEPENDPATH += $$PWD/../../../../../../boost/boost_mingw_4_9/include/boost-1_64



INCLUDEPATH += $$PWD/../../../../../../tbb/include
DEPENDPATH += $$PWD/../../../../../../tbb/include
