#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T11:59:58
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GaitAnalysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sensordatacollector.cpp

HEADERS  += mainwindow.h \
    sensordatacollector.h

FORMS    += mainwindow.ui
