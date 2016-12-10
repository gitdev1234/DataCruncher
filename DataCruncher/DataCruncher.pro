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


INCLUDEPATH += include/
INCLUDEPATH += test/

SOURCES += main.cpp \
    src/VectorData.cpp \
    src/DataCruncher.cpp \
    test/VectorDataTest.cpp \
    test/DataCruncherTest.cpp \
    test/MiscellaneousTest.cpp

HEADERS += \
    catch.hpp \
    include/VectorData.h \
    include/DataCruncher.h \
    include/catch.hpp \
    include/Types.h
