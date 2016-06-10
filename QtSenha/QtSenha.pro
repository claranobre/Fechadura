#-------------------------------------------------
#
# Project created by QtCreator 2016-06-09T16:44:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSenha
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socket.cpp

HEADERS  += mainwindow.h \
    socket.h \
    clientecomando.h

FORMS    += mainwindow.ui
