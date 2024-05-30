#-------------------------------------------------
#
# Project created by QtCreator 2017-12-04T15:15:25
#
#-------------------------------------------------

QT       -= core gui

win32:TARGET = ../../../dist/bin/glazingsolarfactor
TEMPLATE = lib

DEFINES += GLAZINGSOLARFACTOR_LIBRARY

SOURCES += glazingsolarfactor.cpp

HEADERS += glazingsolarfactor.h\
        glazingsolarfactor_global.h

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

unix {
    LIBS += -L$$OUT_PWD/3rdparties/boost/stage/lib -lboost_mpi -lboost_system -lboost_thread -lboost_chrono -lboost_atomic -lboost_date_time -lpthread
    INCLUDEPATH += $$OUT_PWD/../../3rdparties/boost/build/include/boost
    DEPENDPATH += $$OUT_PWD/../../3rdparties/boost/build/include/boost
}

win32: LIBS += -L$$OUT_PWD/../../dist/bin -lcomponents
unix: LIBS += -L$$OUT_PWD/modules/components/ -lcomponents

INCLUDEPATH += $$PWD/../../modules/components
DEPENDPATH += $$PWD/../../modules/components
