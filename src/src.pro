######################################################################
# Automatically generated by qmake (3.1) Thu Nov 29 17:42:15 2018
######################################################################

unix:CONFIG += link_pkgconfig

TEMPLATE = app
TARGET = ld43
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Windows doesn't know Pi
win32:DEFINES += M_PI=3.14159265358979323846

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += main.cpp \
    states/LogoState.cpp \
    states/DummyState.cpp \
    StateHandler.cpp \
    states/TransitionState.cpp

HEADERS += \
    states/LogoState.h \
    IState.h \
    states/DummyState.h \
    Utility.h \
    StateHandler.h \
    states/TransitionState.h

unix:PKGCONFIG += sfml-all

debug:win32:LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-system-d -lsfml-window-d
release:win32:LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window