#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T11:59:58
#
#-------------------------------------------------

QT       += core gui bluetooth

CONFIG  += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GaitAnalysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sensordatacollector.cpp \
    sensorcontroller.cpp \
    sensorplot.cpp \
    footsensorcontroller.cpp \
    accelerometercontroller.cpp \
    incrementalplot.cpp

HEADERS  += mainwindow.h \
    sensordatacollector.h \
    sensorcontroller.h \
    sensorplot.h \
    footsensorcontroller.h \
    accelerometercontroller.h \
    incrementalplot.h

FORMS    += mainwindow.ui
