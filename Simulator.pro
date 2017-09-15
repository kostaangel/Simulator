#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T22:09:22
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulator
TEMPLATE = app

LIBS += -lz

SOURCES += main.cpp\
        simulator_test.cpp \
    qcompressor.cpp

HEADERS  += simulator_test.h \
    qcompressor.h
