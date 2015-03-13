#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T01:15:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Muistikirja
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filehandler.cpp \
    changeattributes.cpp \
    settingshandler.cpp

HEADERS  += mainwindow.h \
    filehandler.h \
    changeattributes.h \
    settingshandler.h

FORMS    += mainwindow.ui

DISTFILES += \
    settings.txt \
    asetukset.txt

