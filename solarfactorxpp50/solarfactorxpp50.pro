#-------------------------------------------------
#
# Project created by QtCreator 2018-07-02T14:17:30
#
#-------------------------------------------------

QT       -= gui
QT      += core

win32:TARGET = ../../../dist/bin/solarfactorxpp50

TEMPLATE = lib
CONFIG += C++11

DEFINES += SOLARFACTORXPP50_LIBRARY

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
            solarfactorxpp50.cpp \
            glazingwall.cpp \
            glazingxp50.cpp \
            frame.cpp \
            opaquewall.cpp \
            mobileprotection.cpp \
            roller.cpp \
            baysolarfactorxpp50.cpp \
            baysolarfactorventilationxpp50.cpp

HEADERS += \
            solarfactorxpp50.h \
            solarfactorxpp50_global.h \
            glazingwall.h \
            glazingxp50.h \
            frame.h \
            opaquewall.h \
            mobileprotection.h \
            roller.h \
            baysolarfactorxpp50.h \
            baysolarfactorventilationxpp50.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32-msvc* {
    LIBS += -L$$OUT_PWD/../../dist/bin \
            -L$$OUT_PWD/../../3rdparties/boost/build/lib

    QMAKE_CXXFLAGS_DEBUG += /Zm159
    QMAKE_CXXFLAGS_RELEASE += /Zm159

    MSVC_VER = $$(VisualStudioVersion)

    equals(MSVC_VER, 12.0){
        CONFIG(release, debug|release) {
            LIBS += -llibboost_thread-vc120-mt-1_64
        } else {
            LIBS += -llibboost_thread-vc120-mt-gd-1_64
        }
    }

    equals(MSVC_VER, 14.0){
        CONFIG(release, debug|release) {
            LIBS += -llibboost_thread-vc140-mt-1_64
        } else {
            LIBS += -llibboost_thread-vc140-mt-gd-1_64
        }
    }

    equals(MSVC_VER, 15.0){
        CONFIG(release, debug|release) {
            LIBS += -llibboost_thread-vc141-mt-1_64
        } else {
            LIBS += -llibboost_thread-vc141-mt-gd-1_64
        }
    }

    INCLUDEPATH += $$OUT_PWD/../../3rdparties/boost/build/include/boost-1_64
    DEPENDPATH += $$OUT_PWD/../../3rdparties/boost/build/include/boost-1_64
}

win32: LIBS += -L$$OUT_PWD/../../dist/bin/ -llibraries
unix: LIBS += -L$$OUT_PWD/modules/libraries/ -llibraries

INCLUDEPATH += $$PWD/../../modules/libraries
DEPENDPATH += $$PWD/../../modules/libraries

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lcomponents
unix: LIBS += -L$$OUT_PWD/modules/components/ -lcomponents

INCLUDEPATH += $$PWD/../../modules/components
DEPENDPATH += $$PWD/../../modules/components

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lprojectcase
unix: LIBS += -L$$OUT_PWD/modules/projectcase/ -lprojectcase

INCLUDEPATH += $$PWD/../../modules/projectcase
DEPENDPATH += $$PWD/../../modules/projectcase

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lcalculation
unix: LIBS += -L$$OUT_PWD/modules/calculation/ -lcalculation

INCLUDEPATH += $$PWD/../../modules/calculation
DEPENDPATH += $$PWD/../../modules/calculation

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lsolarcharacteristics
unix: LIBS += -L$$OUT_PWD/core/solarcharacteristics/ -lsolarcharacteristics

INCLUDEPATH += $$PWD/../solarcharacteristics
DEPENDPATH += $$PWD/../solarcharacteristics

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lbaysolarfactor
unix: LIBS += -L$$OUT_PWD/core/baysolarfactor/ -lbaysolarfactor

INCLUDEPATH += $$PWD/../baysolarfactor
DEPENDPATH += $$PWD/../baysolarfactor

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lbaysolarfactorventilation
unix: LIBS += -L$$OUT_PWD/core/baysolarfactorventilation/ -lbaysolarfactorventilation

INCLUDEPATH += $$PWD/../baysolarfactorventilation
DEPENDPATH += $$PWD/../baysolarfactorventilation
