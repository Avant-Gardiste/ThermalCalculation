#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T16:22:35
#
#-------------------------------------------------

QT       -= core gui

CONFIG += c++11

win32:TARGET = ../../../dist/bin/components
unix:TARGET = components

TEMPLATE = lib

DEFINES += COMPONENTS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
            conditionoutside.cpp \
            defineglass.cpp \
            gasgap.cpp \
            glazingsituation.cpp \
            information.cpp \
            module.cpp \
            spectral.cpp \
            blindvd.cpp \
            filmvd.cpp \
            glassvd.cpp \
            pvbvd.cpp \
            defineblind.cpp \
            result.cpp \
            clientinfo.cpp \
            cebtpcompany.cpp \
            climateconditions.cpp \
            obstaclevd.cpp \
            glazingdtu39.cpp

HEADERS += \
            components_global.h \
            conditionoutside.h \
            defineglass.h \
            gasgap.h \
            glazingsituation.h \
            information.h \
            module.h \
            spectral.h \
            blindvd.h \
            filmvd.h \
            glassvd.h \
            pvbvd.h \
            defineblind.h \
            object.h \
            result.h \
            clientinfo.h \
            cebtpcompany.h \
            climateconditions.h \
            defineconstants.h \
            obstaclevd.h \
            workshop.h \
            glazingdtu39.h \
            common.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
