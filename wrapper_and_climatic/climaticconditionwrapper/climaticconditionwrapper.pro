#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T13:57:48
#
#-------------------------------------------------

QT       -= gui
QT       += core

win32: TARGET = ../../../dist/bin/climaticconditionwrapper
unix:TARGET = climaticconditionwrapper

TEMPLATE = lib

DEFINES += CLIMATICCONDITIONWRAPPER_LIBRARY

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
            climaticconditionwrapper.cpp \
            baysolarfactorclimaticconditions.cpp \
            baseclimaticcondition.cpp \
            climatic.cpp \
            glazingsolarfactorclimaticcondition.cpp \
            glazinguvalueclimaticcondition.cpp \
            tmaxsealingjointclimaticcondition.cpp \
            thermalbreakageclimaticcondition.cpp

HEADERS += \
            climaticconditionwrapper.h \
            climaticconditionwrapper_global.h \
            baysolarfactorclimaticconditions.h \
            baseclimaticcondition.h \
            climatic.h \
            glazingsolarfactorclimaticcondition.h \
            glazinguvalueclimaticcondition.h \
            tmaxsealingjointclimaticcondition.h \
            thermalbreakageclimaticcondition.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:LIBS += -L$$OUT_PWD/../../dist/bin/ -llibraries
unix: LIBS += -L$$OUT_PWD/modules/libraries/ -llibraries

INCLUDEPATH += $$PWD/../../modules/libraries
DEPENDPATH += $$PWD/../../modules/libraries

win32:LIBS += -L$$OUT_PWD/../../dist/bin/ -lcomponents
unix: LIBS += -L$$OUT_PWD/modules/components/ -lcomponents

INCLUDEPATH += $$PWD/../../modules/components
DEPENDPATH += $$PWD/../../modules/components

win32:LIBS += -L$$OUT_PWD/../dist/bin/ -lprojectcase
unix: LIBS += -L$$OUT_PWD/modules/projectcase/ -lprojectcase

INCLUDEPATH += $$PWD/../../modules/projectcase
DEPENDPATH += $$PWD/../../modules/projectcase
