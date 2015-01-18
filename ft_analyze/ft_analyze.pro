#-------------------------------------------------
#
# Project created by QtCreator 2014-05-19T20:24:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ft_analyze
TEMPLATE = app

include(ft_configure.pri)

SOURCES += main.cpp \
    host/ocldft.cpp \
    host/utils.cpp \
    app/mainwindow.cpp \
    app/wavfile.cpp \
    app/controller.cpp \
    app/model.cpp \
    app/qfunc3d.cpp \
    host/dft.cpp

OTHER_FILES += \
    device/dft.cl

HEADERS += \
    host/ifouriertransform.h \
    host/ocldft.h \
    host/utils.h \
    app/mainwindow.h \
    app/wavfile.h \
    app/controller.h \
    app/model.h \
    app/qfunc3d.h \
    host/dft.h

FORMS += \
    app/mainwindow.ui
