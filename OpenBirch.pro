QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    expressionparser.cpp \
    expressions.cpp \
    main.cpp \
    mainwindow.cpp \
    mathedit.cpp \
    operands.cpp \
    parsertree.cpp \
    symboltable.cpp

HEADERS += \
    expressiondatatypes.h \
    expressionparser.h \
    expressions.h \
    mainwindow.h \
    mathedit.h \
    operands.h \
    parsertree.h \
    symboltable.h \
    typedef.h

FORMS += \
    mainwindow.ui

MAKEFLAGS += -j s%NUMBER_OF_PROCESSORS%

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
