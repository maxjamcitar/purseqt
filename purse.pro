#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T23:30:23
#
#-------------------------------------------------

QT       += core gui widgets network charts

TARGET = purseqt
TEMPLATE = app


SOURCES +=  src/main.cpp \
    src/expense.cpp \
    src/income.cpp \
    src/money.cpp \
    src/manager.cpp \
    src/transaction.cpp \
    ui/dialogaddexpense.cpp \
    ui/dialogaddincome.cpp \
    ui/dialogeditexpense.cpp \
    ui/dialogeditincome.cpp \
    ui/dialogresidualchart.cpp \
    ui/mainwindow.cpp

HEADERS  += src/expense.h \
    src/income.h \
    src/money.h \
    src/manager.h \
    src/transaction.h \
    ui/dialogaddexpense.h \
    ui/dialogaddincome.h \
    ui/dialogeditexpense.h \
    ui/dialogeditincome.h \
    ui/dialogresidualchart.h \
    ui/mainwindow.h

FORMS    += \
    ui/dialogaddexpense.ui \
    ui/dialogaddincome.ui \
    ui/dialogeditexpense.ui \
    ui/dialogeditincome.ui \
    ui/dialogresidualchart.ui \
    ui/mainwindow.ui
