QT += widgets

TEMPLATE = lib
CONFIG += dll
DEFINES += MAKE_WAITING_SPINNER_LIB

TARGET = qtwaitingspinner

SOURCES += \
    waitingspinnerwidget.cpp
    
HEADERS += \
    waitingspinnerwidget.h

###############################
# BUILD
###############################
CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

