#-------------------------------------------------
#
# Project created by QtCreator 2018-08-25T02:44:13
#
#-------------------------------------------------

QT       += core gui serialbus
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openecar_dashboard
TEMPLATE = app

INCLUDEPATH += ../can-proto

SOURCES += main.cpp\
        opencardashboard.cpp \
    ../can-proto/canproto.cpp \
    config.cpp

HEADERS  += opencardashboard.h \
    ../can-proto/canproto.h \
    config.h \
    revision.h

FORMS    += opencardashboard.ui

RESOURCES += \
    pictures.qrc

DISTFILES +=
