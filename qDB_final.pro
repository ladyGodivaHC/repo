#-------------------------------------------------
#
# Project created by QtCreator 2014-07-12T12:42:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qDB_final
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmodel.cpp \
    instruments.cpp \
    guitar.cpp \
    smartinstrument.cpp \
    searchfunctor.cpp \
    genericcontainer.cpp \
    modifyfunctor.cpp \
    piano.cpp

HEADERS  += mainwindow.h \
    genericcontainer.h \
    qmodel.h \
    instruments.h \
    guitar.h \
    smartinstrument.h \
    searchfunctor.h \
    modifyfunctor.h \
    piano.h

FORMS    += mainwindow.ui
