# This part of gap under license GNU GPL (c) 2020 Kirill Pshenichnyi

QT += core gui widgets printsupport

TARGET = gap
TEMPLATE = app

SOURCES += \
        src/sansdata.cpp \
        src/main.cpp \
        src/mainwindow.cpp

HEADERS += \
        src/sansdata.h \
        src/mainwindow.h

INCLUDEPATH += \
            src/ 

