#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T14:08:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LedBillboard
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += gui/mainwindow.cpp \
    main.cpp \
    service/billboardservice.cpp \
    gui/mediawindow.cpp \
    model/playlist.cpp \
    service/apiservice.cpp \
    settings.cpp \
    service/playlistservice.cpp \
    model/mediacontent.cpp

HEADERS += gui/mainwindow.h \
    service/billboardservice.h \
    gui/mediawindow.h \
    model/playlist.h \
    service/apiservice.h \
    settings.h \
    service/playlistservice.h \
    singleton.h \
    model/mediacontent.h

FORMS += gui/mainwindow.ui \
    gui/mediawindow.ui

win32:CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtCore.dll \
        -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtQml.dll \
        -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtWidgets.dll
} else {
    win32:CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtCored.dll \
            -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtQmld.dll \
            -L$$PWD/../3rdparty/VLCQt/lib/ -llibVLCQtWidgetsd.dll
    }
}

INCLUDEPATH += $$PWD/../3rdparty/VLCQt/include
DEPENDPATH += $$PWD/../3rdparty/VLCQt/include
