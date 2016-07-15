#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T14:01:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SignalProcessor
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    src/SignalProcessor.cpp

HEADERS += \
    catch.hpp \
    include/signal_template.h \
    include/SignalProcessor.h \
    include/SignalProcessor_template.h
