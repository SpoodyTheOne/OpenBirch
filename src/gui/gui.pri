INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/expression_tree_visualizer/expressiontreevisualizer.ui \
    $$PWD/mainwindow.ui \
    #$$PWD/deprecated/matheditline.ui \
    #$$PWD/deprecated/matheditoutput.ui \
    #$$PWD/deprecated/worksheet.ui \
    #$$PWD/deprecated/worksheetline.ui \
    $$PWD/worksheet.ui

HEADERS += \
    $$PWD/expression_tree_visualizer/expressiontreevisualizer.h \
    $$PWD/expression_tree_visualizer/iinformationalnode.h \
    $$PWD/mainwindow.h \
    #$$PWD/deprecated/matheditline.h \
    #$$PWD/deprecated/matheditoutput.h \
    #$$PWD/deprecated/mathexpressionline.h \
    #$$PWD/deprecated/worksheet.h \
    #$$PWD/deprecated/worksheetline.h \
    $$PWD/worksheet.h

SOURCES += \
    $$PWD/expression_tree_visualizer/expressiontreevisualizer.cpp \
    $$PWD/mainwindow.cpp \
    #$$PWD/deprecated/matheditline.cpp \
    #$$PWD/deprecated/matheditoutput.cpp \
    #$$PWD/deprecated/mathexpressionline.cpp \
    #$$PWD/deprecated/worksheet.cpp \
    #$$PWD/deprecated/worksheetline.cpp \
    $$PWD/worksheet.cpp
