# This part of gap under license GNU GPL (c) 2020 Kirill Pshenichnyi

QT += core gui widgets printsupport

TARGET = gap
TEMPLATE = app

SOURCES += \
        src/importfile.cpp \
        src/sansdata.cpp \
        src/main.cpp \
        src/mainwindow.cpp

HEADERS += \
        src/importfile.h \
        src/sansdata.h \
        src/mainwindow.h

INCLUDEPATH += \
            src/ 

