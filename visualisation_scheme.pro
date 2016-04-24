#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T13:04:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualisation_scheme
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    translation_funcs.cpp \
    data_holder.cpp

HEADERS  += window.h \
    data_holder.h
QT += opengl

