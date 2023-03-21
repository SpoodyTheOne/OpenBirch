#include "tst_postfix_convert.h"

#include "base/deprecated/expression_parser/postfix_parser/postfixparser.h"
#include <QString>
#include <QTest>

void tst_postfix_convert::RunSimple()
{
    QCOMPARE(QString(PostFixParser::parseExpression("2+2").c_str()), QString("2 2 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("2-2").c_str()), QString("2 2 - "));
    QCOMPARE(QString(PostFixParser::parseExpression("15+11").c_str()), QString("15 11 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("17-4").c_str()), QString("17 4 - "));
    QCOMPARE(QString(PostFixParser::parseExpression("2*2").c_str()), QString("2 2 * "));
    QCOMPARE(QString(PostFixParser::parseExpression("10*10").c_str()), QString("10 10 * "));
    QCOMPARE(QString(PostFixParser::parseExpression("4/6").c_str()), QString("4 6 / "));
    QCOMPARE(QString(PostFixParser::parseExpression("18725+97128").c_str()), QString("18725 97128 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("12345*98765").c_str()), QString("12345 98765 * "));
}

void tst_postfix_convert::RunMultipleTerms()
{
    QCOMPARE(QString(PostFixParser::parseExpression("2+2+2").c_str()), QString("2 2 + 2 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("2+2+2+2").c_str()), QString("2 2 + 2 + 2 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("2+2+2").c_str()), QString("2 2 + 2 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("2+2+2").c_str()), QString("2 2 + 2 + "));
}


void tst_postfix_convert::RunPrecedenceOrder()
{
    QCOMPARE(QString(PostFixParser::parseExpression("4+2*3").c_str()), QString("4 2 3 * + "));
    QCOMPARE(QString(PostFixParser::parseExpression("5*2+4").c_str()), QString("5 2 * 4 + "));
    QCOMPARE(QString(PostFixParser::parseExpression("5/2-4").c_str()), QString("5 2 / 4 - "));
}

void tst_postfix_convert::RunWithParenthesis()
{
    QCOMPARE(QString(PostFixParser::parseExpression("2*(2+2)").c_str()), QString("2 2 2 + * "));
    QCOMPARE(QString(PostFixParser::parseExpression("(1-4)*(5+3)").c_str()), QString("1 4 - 5 3 + * "));
    QCOMPARE(QString(PostFixParser::parseExpression("(5-3)/(4+4)").c_str()), QString("5 3 - 4 4 + / "));
}
