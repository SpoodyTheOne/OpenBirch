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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lgmpxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lgmpxx
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lgmpxx

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/release/libgmpxx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/debug/libgmpxx.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/release/gmpxx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/debug/gmpxx.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/libgmpxx.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lgmp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lgmp
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lgmp

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/release/libgmp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/debug/libgmp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/release/gmp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/debug/gmp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../usr/lib/libgmp.a
