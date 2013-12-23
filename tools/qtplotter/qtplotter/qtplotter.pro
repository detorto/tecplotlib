#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T02:02:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtplotter
TEMPLATE = app

CONFIG += c++11

LIBS += -L../../../lib/ -ltecplotlib -lmgl -lmgl-qt
INCLUDEPATH += ../../../include/

SOURCES += main.cpp\
        plotterwindow.cpp \
    FileOpener.cpp

HEADERS  += plotterwindow.h \
    FileOpener.h

FORMS    += plotterwindow.ui

QMAKE_CXXFLAGS += -Wall -fPIC -std=c++11
