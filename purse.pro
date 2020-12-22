#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T23:30:23
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = purseqt
TEMPLATE = app


SOURCES +=  src/main.cpp \
    src/expense.cpp \
    src/income.cpp \
    src/money.cpp \
    src/manager.cpp \
    src/transaction.cpp \
    ui/editexpense.cpp \
    ui/editincome.cpp \
    ui/mainwindow.cpp \
    ui/addexpense.cpp \
    ui/addincome.cpp

HEADERS  += src/expense.h \
    src/income.h \
    src/money.h \
    src/manager.h \
    src/transaction.h \
    ui/editexpense.h \
    ui/editincome.h \
    ui/mainwindow.h \
    ui/addexpense.h \
    ui/addincome.h

FORMS    += ui/addexpense.ui \
    ui/addincome.ui \
    ui/editexpense.ui \
    ui/editincome.ui \
    ui/mainwindow.ui
