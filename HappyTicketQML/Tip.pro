TEMPLATE = app

TARGET = HappyTicket

QT += qml quick
SOURCES += main.cpp \
#    BigIntLib/BigInteger.cc \
#    BigIntLib/BigIntegerAlgorithms.cc \
#    BigIntLib/BigIntegerUtils.cc \
#    BigIntLib/BigUnsigned.cc \
#    BigIntLib/BigUnsignedInABase.cc \
    bustthread.cpp \
    thrwrap.cpp

INSTALLS += target qml

#win32:RC_FILE += app.rc

OTHER_FILES += \
    qml/main.qml \
    qml/Slider.qml \
    qml/Indicator.qml \
    qml/Button.qml \
    qml/AbstractBusyIndicator.qml \
    qml/BusyIndicator.qml \
    qml/Info.qml

HEADERS += \
#    BigIntLib/BigInteger.hh \
#    BigIntLib/BigIntegerAlgorithms.hh \
#    BigIntLib/BigIntegerLibrary.hh \
#    BigIntLib/BigIntegerUtils.hh \
#    BigIntLib/BigUnsigned.hh \
#    BigIntLib/BigUnsignedInABase.hh \
#    BigIntLib/NumberlikeArray.hh \
    bustthread.h \
    thrwrap.h
