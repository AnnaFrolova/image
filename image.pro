QT += core

CONFIG += c++11

TARGET = image
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    bitmap.cpp

HEADERS += \
    pixel.h \
    bitmap.h
