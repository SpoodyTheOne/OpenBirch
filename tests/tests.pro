# Expression result tst is dependent on expression parser:
include(../src/base/base.pri)

QT +=  testlib

CONFIG += c++17 console
CONFIG -= app_bundle

unix: LIBS += -L"/usr/lib64/" -lgmp -lgmpxx -lmpfr

INCLUDEPATH += $$PWD/../src

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    tst_expression_result.cpp \
    tst_number_arithmetics.cpp \
    tst_postfix_convert.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    tst_expression_result.h \
    tst_number_arithmetics.h \
    tst_postfix_convert.h
