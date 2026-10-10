QT       -= gui

CONFIG   += c++17 console
CONFIG   -= app_bundle

TARGET = LR1_Protector
TEMPLATE = app

SOURCES += main.cpp

win32 {
    LIBS += -ladvapi32
}
