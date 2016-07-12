#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T23:33:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanjiMaker
TEMPLATE = app


SOURCES += main.cpp\
        mainw.cpp \
    wordlistwidget.cpp \
    com/listwidget.cpp \
    wordpadwidget.cpp \
    kanapadwidget.cpp \
    com/kanapushbutton.cpp \
    com/lineedit.cpp \
    previewwidget.cpp

HEADERS  += mainw.h \
    wordlistwidget.h \
    com/listwidget.h \
    wordpadwidget.h \
    kanapadwidget.h \
    com/kanapushbutton.h \
    com/lineedit.h \
    previewwidget.h
