TEMPLATE = app

CONFIG += console

TARGET = HappyTicket

QT += qml quick
SOURCES += main.cpp \
    bustthread.cpp \
    thrwrap.cpp

INSTALLS += target qml

OTHER_FILES += \
    qml/main.qml \
    qml/Slider.qml \
    qml/Indicator.qml \
    qml/Button.qml \
    qml/AbstractBusyIndicator.qml \
    qml/BusyIndicator.qml \
    qml/Info.qml \

HEADERS += \
    bustthread.h \
    thrwrap.h

RESOURCES += \
    qml.qrc
