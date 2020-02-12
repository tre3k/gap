# This part of gap under license GNU GPL (c) 2020 Kirill Pshenichnyi

QT += core gui widgets printsupport

TARGET = gap
TEMPLATE = app

SOURCES += \
        src/centralwidget.cpp \
        src/generealwidget.cpp \
        src/globalclass.cpp \
        src/importfile.cpp \
        src/importfileswidget.cpp \
        src/sansdata.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/plots.cpp \
        src/external/qcustomplot.cpp \
        src/sansdataviewer.cpp \
        src/toolwidgets.cpp \
        src/dialogs.cpp

HEADERS += \
        src/centralwidget.h \
        src/generealwidget.h \
        src/globalclass.h \
        src/importfile.h \
        src/importfileswidget.h \
        src/sansdata.h \
        src/mainwindow.h \
        src/plots.h \
        src/external/qcustomplot.h \
        src/sansdataviewer.h \
        src/toolwidgets.h \
        src/dialogs.h

INCLUDEPATH += \
            src/ \
            src/external

RESOURCES += \
    resources.qrc

