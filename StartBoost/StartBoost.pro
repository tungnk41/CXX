TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32 {
    INCLUDEPATH += C:\boost\include
    LIBS += "-LC:\boost\lib\shared"
}

debug {
    DESTDIR = debug
    OBJ_DIR = debug
}
release
{
    DESTDIR = release
    OBJ_DIR = release
}
