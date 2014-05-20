#-------------------------------------------------
#
# Project created by QtCreator 2014-05-19T20:24:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ft_analyze
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    host/ocldft.cpp \
    host/utils.cpp


INCLUDEPATH += "3rdparty\include"
 win32:LIBS += "3rdparty\lib\x86\OpenCL.lib"

OTHER_FILES += \
    device/dft.cl

HEADERS += \
    host/ifouriertransform.h \
    host/ocldft.h \
    host/utils.h
