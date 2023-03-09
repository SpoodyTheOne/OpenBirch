#include "tst_expression_result.h"

#include <QTest>
#include <iostream>
#include <ostream>
#include "base/expression_parser/types.h"

void tst_expression_result::RunAdditionTests()
{
    //QCOMPARE(m_ExpressionParser.parseString("2+2"), QString("4"));

    Number test;
    QCOMPARE(QString(test.print().c_str()),QString("0"));

    test = 1;
    QCOMPARE(QString(test.print().c_str()),QString("1"));

    test += 2;
    QCOMPARE(QString(test.print().c_str()),QString("3"));
}

// For running test as a standalone executable
QTEST_APPLESS_MAIN(tst_expression_result);
