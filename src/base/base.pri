# DEPRECATED
#HEADERS += \
#    $$PWD/deprecated/expression_parser/constantnode.h \
#    $$PWD/deprecated/expression_parser/node.h \
#    $$PWD/deprecated/expression_parser/operatornode.h \
#    $$PWD/deprecated/expression_parser/parser.h \
#    $$PWD/deprecated/expression_parser/postfix_parser/postfixparser.h \
#    $$PWD/deprecated/expression_parser/symboltable.h \
#    $$PWD/deprecated/expression_parser/tree.h \
#    $$PWD/expression_parser/solver.h \
#    $$PWD/expressionvalue.h \
#    $$PWD/deprecated/expression_parser/variablenode.h \
#    $$PWD/deprecated/operators/abs.h \
#    $$PWD/deprecated/operators/addition.h \
#    $$PWD/deprecated/operators/cos.h \
#    $$PWD/deprecated/operators/division.h \
#    $$PWD/deprecated/operators/equals.h \
#    $$PWD/deprecated/operators/exponent.h \
#    $$PWD/deprecated/operators/factorial.h \
#    $$PWD/deprecated/operators/multiply.h \
#    $$PWD/deprecated/operators/negate.h \
#    $$PWD/deprecated/operators/operator.h \
#    $$PWD/deprecated/operators/operatorfactory.h \
#    $$PWD/deprecated/operators/parenthesis.h \
#    $$PWD/deprecated/operators/sin.h \
#    $$PWD/deprecated/operators/square_root.h \
#    $$PWD/deprecated/operators/subtraction.h \
#    $$PWD/deprecated/operators/sum.h
#
#
#SOURCES += \
#    $$PWD/deprecated/expression_parser/constantnode.cpp \
#    $$PWD/deprecated/expression_parser/node.cpp \
#    $$PWD/deprecated/expression_parser/operatornode.cpp \
#    $$PWD/deprecated/expression_parser/parser.cpp \
#    $$PWD/deprecated/expression_parser/postfix_parser/postfixparser.cpp \
#    $$PWD/deprecated/expression_parser/symboltable.cpp \
#    $$PWD/deprecated/expression_parser/tree.cpp \
#    $$PWD/deprecated/expression_parser/variablenode.cpp \
#    $$PWD/deprecated/operators/operator.cpp \
#    $$PWD/deprecated/operators/operatorfactory.cpp \
#    $$PWD/expression_parser/solver.cpp
#DEPRECATED END


HEADERS += \
    $$PWD/expression_parser/mathengine.h \
    $$PWD/nodes/constantnode.h \
    $$PWD/nodes/node.h \
    $$PWD/nodes/operatornode.h \
    $$PWD/nodes/variablenode.h \
    $$PWD/operators/abs.h \
    $$PWD/operators/addition.h \
    $$PWD/operators/cos.h \
    $$PWD/operators/division.h \
    $$PWD/operators/equals.h \
    $$PWD/operators/exponent.h \
    $$PWD/operators/factorial.h \
    $$PWD/operators/multiply.h \
    $$PWD/operators/negate.h \
    $$PWD/operators/operator.h \
    $$PWD/operators/operatorfactory.h \
    $$PWD/operators/parenthesis.h \
    $$PWD/operators/sin.h \
    $$PWD/operators/square_root.h \
    $$PWD/operators/subtraction.h \
    $$PWD/operators/sum.h \
    $$PWD/expression_parser/solver.h \
    $$PWD/postfixparser.h \
    $$PWD/symboltable/symboltable.h

SOURCES += \
    $$PWD/expression_parser/mathengine.cpp \
    $$PWD/nodes/constantnode.cpp \
    $$PWD/nodes/node.cpp \
    $$PWD/nodes/operatornode.cpp \
    $$PWD/nodes/variablenode.cpp \
    $$PWD/operators/operator.cpp \
    $$PWD/operators/operatorfactory.cpp \
    $$PWD/expression_parser/solver.cpp \
    $$PWD/postfixparser.cpp \
    $$PWD/symboltable/symboltable.cpp
