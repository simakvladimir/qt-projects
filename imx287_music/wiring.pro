# avoid error dynamic_cast_will_always_fail_because_rtti_is_disabled in 4.8.3
CONFIG += rtti
CONFIG += qaxcontainer qaxwidget

#CONFIG += qt
#QT       += core gui

TEMPLATE = app
TARGET   = COM_diode
QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#QT += core gui widgets


# Codecs
CODECFORSRC = UTF-8
CODECFORTR = UTF-8

SOURCES += \
    main.cpp \
    diodeview.cpp \
    diodepresenter.cpp \
    diodemodel.cpp \
    gradient.cpp \
    comport.cpp \
    portaudiowrapper.cpp \
    fftwcompute.cpp \
    buffer/safebuffer.cpp \
    eq/equalizer.cpp \
    fftw_thread.cpp

HEADERS += \
    diodeview.h \
    idiodeview.h \
    diodepresenter.h \
    diodemodel.h \
    gradient.h \
    comport.h \
    portaudiowrapper.h \
    fftwcompute.h \
    buffer/safebuffer.h \
    eq/equalizer.h \
    fftw_thread.h \
    buffer/common.h

FORMS += \
    diodeview.ui

LIBS += portaudio/portaudio_x86.lib\
        fftw/libfftw3-3.dll\



include(comport/src/qextserialport.pri)
