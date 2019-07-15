#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T19:20:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = goldMiner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        GoldenMiner1/mywidget1.cpp \
        data.cpp \
        drawline.cpp \
        firstlevel.cpp \
        main.cpp \
        beginmainwindow.cpp \
        mywidget.cpp \
        secondleveln.cpp \
        widget.cpp

HEADERS += \
        GoldenMiner1/mywidget1.h \
        beginmainwindow.h \
        data.h \
        drawline.h \
        firstlevel.h \
        mywidget.h \
        secondleveln.h \
        widget.h

FORMS += \
        GoldenMiner1/mywidget.ui \
        beginmainwindow.ui \
        firstlevel.ui \
        secondleveln.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc
