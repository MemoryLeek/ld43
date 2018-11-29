######################################################################
# Automatically generated by qmake (3.1) Thu Nov 29 17:42:15 2018
######################################################################

CONFIG += link_pkgconfig

TEMPLATE = app
TARGET = ld43
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += main.cpp \
    states/LogoState.cpp \
    StateTransition.cpp \
    states/DummyState.cpp \
    StateHandler.cpp \
    states/TransitionState.cpp

PKGCONFIG += sfml-all

HEADERS += \
    states/LogoState.h \
    IState.h \
    StateTransition.h \
    states/DummyState.h \
    Utility.h \
    StateHandler.h \
    states/TransitionState.h
