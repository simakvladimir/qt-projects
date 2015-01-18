#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T10:25:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = convolution
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -mavx -fopenmp
INCLUDEPATH += 3rdparty\include

LIBS += 3rdparty\lib\x86\OpenCL.lib
LIBS += -lgomp

SOURCES += main.cpp \
    c_native.cpp \
    c_avx.cpp \
    c_avx_openmp.cpp \
    open_cl.cpp

HEADERS += \
    c_native.h \
    c_avx.h \
    c_avx_openmp.h \
    open_cl.h

OTHER_FILES += \
    OpenCl.cl
