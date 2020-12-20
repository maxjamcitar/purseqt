#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T23:30:23
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = purseqt
TEMPLATE = app


SOURCES += src/main.cpp \
    addexpense.cpp \
    addincome.cpp \
    mainwindow.cpp \
    src/expense.cpp \
    src/income.cpp \
    src/money.cpp \
    src/manager.cpp \
    src/transaction.cpp

HEADERS  += addexpense.h \
    addincome.h \
    mainwindow.h \
    src/expense.h \
    src/income.h \
    src/money.h \
    src/manager.h \
    src/transaction.h

FORMS    += addexpense.ui \
    addincome.ui \
    mainwindow.ui
