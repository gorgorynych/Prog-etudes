#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T10:01:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamescene.cpp

HEADERS  += mainwindow.h \
    gamescene.h

FORMS    += mainwindow.ui
