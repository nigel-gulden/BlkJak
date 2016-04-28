TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    Blackjack.cpp \
    Deck.cpp \
    Hand.cpp \
    CardC.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Blackjack.h \
    Deck.h \
    Hand.h \
    Random.h \
    CardC.h
