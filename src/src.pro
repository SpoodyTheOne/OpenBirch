TEMPLATE = app
TARGET = OpenBirch

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(app/app.pri)
include(base/base.pri)
include(gui/gui.pri)

# Use all threads for compilation
MAKEFLAGS += -j s%NUMBER_OF_PROCESSORS%

RESOURCES += \
    Resources.qrc

unix: LIBS += -L"/usr/lib64/" -lgmp -lgmpxx
