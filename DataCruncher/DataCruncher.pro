#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T14:01:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = DataCruncher
CONFIG   += console
CONFIG   -= app_bundle
#CONFIG   += c++11
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += main.cpp \
    src/DataCruncher.cpp

HEADERS += \
    catch.hpp \
    include/DataCruncher.h
