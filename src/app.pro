#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T13:47:00
#
#-------------------------------------------------

QT     += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

TARGET = bdtitles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chapterswidget.cpp

HEADERS  += mainwindow.h \
    chapterswidget.h

LIBS += -lbluray
