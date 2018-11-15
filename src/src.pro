#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T00:14:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChickenLauncherReborn
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/newprofiledialog.cpp \
    core/settings.cpp \
    core/directorylist.cpp \
    core/tablehelper.cpp \
    core/listhelper.cpp \
    games/gzdoom.cpp \
    ui/aboutdialog.cpp

HEADERS  += ui/mainwindow.h \
            ui/newprofiledialog.h \
            core/settings.h \
    core/directorylist.h \
    core/tablehelper.h \
    core/listhelper.h \
    games/common.h \
    games/gzdoom.h \
    ui/aboutdialog.h

FORMS    += ui/mainwindow.ui \
    ui/newprofiledialog.ui \
    ui/aboutdialog.ui

RESOURCES += \
    icon.qrc
