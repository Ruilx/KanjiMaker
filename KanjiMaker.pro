#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T23:33:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += -std=c++11

TARGET = KanjiMaker
TEMPLATE = app


SOURCES += \
aboutwidget.cpp \
kanapadwidget.cpp \
main.cpp \
mainw.cpp \
previewwidget.cpp \
wordlistwidget.cpp \
wordpadwidget.cpp \
com/graphicsview.cpp \
com/kanapushbutton.cpp \
com/lineedit.cpp \
com/listwidget.cpp \
core/readsavefile.cpp


HEADERS  += \
aboutwidget.h \
kanapadwidget.h \
mainw.h \
previewwidget.h \
wordlistwidget.h \
wordpadwidget.h \
com/graphicsview.cpp \
com/graphicsview.h \
com/kanapushbutton.cpp \
com/kanapushbutton.h \
com/lineedit.h \
com/listwidget.h \
core/about.h \
core/readsavefile.h \
core/structure.h

RESOURCES += resource.qrc \
resource.rc

TRANSLATIONS += zh_CN.UTF-8.ts
