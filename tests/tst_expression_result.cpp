#include "tst_expression_result.h"
#include "base/expression_parser/expressionparser.h"

#include <QTest>

void tst_expression_result::RunAdditionTests()
{
    QCOMPARE(m_ExpressionParser.parseString("2+2"), QString("4"));
    QCOMPARE(m_ExpressionParser.parseString("2+5"), QString("7"));
    QCOMPARE(m_ExpressionParser.parseString("5+5"), QString("10"));
    QCOMPARE(m_ExpressionParser.parseString("10+0"), QString("10"));
    QCOMPARE(m_ExpressionParser.parseString("2+8"), QString("10"));
    QCOMPARE(m_ExpressionParser.parseString("0+10"), QString("10"));
    QCOMPARE(m_ExpressionParser.parseString("2+2+2"), QString("6"));
    QCOMPARE(m_ExpressionParser.parseString("4+8"), QString("12"));
    QCOMPARE(m_ExpressionParser.parseString("12+6"), QString("18"));
    QCOMPARE(m_ExpressionParser.parseString("3+3+3+3"), QString("12"));
    QCOMPARE(m_ExpressionParser.parseString("1+1+1+1+1+1+1+1+1+1"), QString("10"));
}

// For running test as a standalone executable
QTEST_APPLESS_MAIN(tst_expression_result);
