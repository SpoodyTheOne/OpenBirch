#include "tst_expression_result.h"
#include "base/deprecated/expression_parser/parser.h"

#include <QTest>
#include <iostream>
#include <ostream>

void tst_expression_result::RunAdditionTests()
{
    Parser parser;
    parser.setExpression(QString("2+2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("4"));

    parser.setExpression(QString("2+8"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("10"));

    parser.setExpression(QString("8+2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("10"));

    parser.setExpression(QString("11+1"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("12"));

    parser.setExpression(QString("5 + 19"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("24"));

    parser.setExpression(QString("14408+21322"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("35730"));
}

void tst_expression_result::RunSubtractionTests()
{
    Parser parser;
    parser.setExpression(QString("2-2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("0"));

    parser.setExpression(QString("2-4"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("-2"));

    parser.setExpression(QString("9-3"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("6"));

    parser.setExpression(QString("99-9-9-9"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("72"));
}


void tst_expression_result::RunMultiplicationTests()
{
    Parser parser;
    parser.setExpression(QString("2*2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("4"));

    parser.setExpression(QString("2*10"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("20"));

    parser.setExpression(QString("10*10*10"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("1000"));

    parser.setExpression(QString("23*52"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("1196"));

    parser.setExpression(QString("2*2*2*2*2*2*2*2*2*2*2*2*2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("8192"));

//    QEXPECT_FAIL("", "Needs support for negation operator", Continue);
//    parser.setExpression(QString("-5*5"));
//    parser.compile();
//    QCOMPARE(parser.evaluate(), QString("-25"));
}


void tst_expression_result::RunDivisionTests()
{
    Parser parser;
    parser.setExpression(QString("2/2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("1"));

    parser.setExpression(QString("2/1"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("2"));

    parser.setExpression(QString("1/2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("0.5"));

    parser.setExpression(QString("20/10"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("2"));

    parser.setExpression(QString("2/2/2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("0.5"));

    parser.setExpression(QString("13/8"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("1.625"));
}

void tst_expression_result::RunExponentTests()
{
    // TODO
}

void tst_expression_result::RunBasicPrecedenceTests()
{
    // TODO
}

void tst_expression_result::RunNegateTests()
{
    Parser parser;
    parser.setExpression(QString("-2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("-2"));

    parser.setExpression(QString("2--2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("4"));

    parser.setExpression(QString("--2"));
    parser.compile();
    QCOMPARE(parser.evaluate(), QString("2"));
}







