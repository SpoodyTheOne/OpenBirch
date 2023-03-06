#include "tst_expression_result.h"
#include "base/expression_parser/expressionparser.h"

#include <QTest>

void tst_expression_result::RunAdditionTests()
{
    QCOMPARE(m_ExpressionParser.parseString("2+2"), "4");
}

// For running test as a standalone executable
QTEST_APPLESS_MAIN(tst_expression_result);
