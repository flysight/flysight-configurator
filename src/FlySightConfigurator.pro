#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T15:11:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlySightConfigurator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    configuration.cpp \
    generalform.cpp \
    configurationpage.cpp \
    toneform.cpp \
    rateform.cpp \
    speechform.cpp \
    thresholdsform.cpp \
    initializationform.cpp

HEADERS  += mainwindow.h \
    configuration.h \
    generalform.h \
    configurationpage.h \
    toneform.h \
    rateform.h \
    speechform.h \
    thresholdsform.h \
    initializationform.h

FORMS    += mainwindow.ui \
    generalform.ui \
    toneform.ui \
    rateform.ui \
    speechform.ui \
    thresholdsform.ui \
    initializationform.ui
