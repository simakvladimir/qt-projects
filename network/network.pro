#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T11:49:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uploader.cpp \
    qupfile.cpp \
    downloader.cpp \
    postjson.cpp \
    getjson.cpp

HEADERS  += mainwindow.h \
    uploader.h \
    qupfile.h \
    downloader.h \
    postjson.h \
    getjson.h

FORMS    += mainwindow.ui
