#-------------------------------------------------
#
# Project created by QtCreator 2014-03-01T14:32:27
#
#-------------------------------------------------

QT       += core gui qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SDKmanager
TEMPLATE = app

INCLUDEPATH += wpcap/Include

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    macwrap.cpp \
    packettable.cpp

HEADERS  += mainwindow.h \
    settings.h \
    macwrap.h \
    rxpacket.h \
    txpacket.h \
    packettable.h

FORMS    += mainwindow.ui \
    settings.ui \
    packettable.ui

OTHER_FILES += \
    qml/main.qml \
    qml/Switch.qml \
    qml/Led.qml \
    qml/Jumper.qml

win32: LIBS += wpcap/Lib/wpcap.lib
