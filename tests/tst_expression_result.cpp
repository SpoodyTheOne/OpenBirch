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

    test *= test;
    QCOMPARE(QString(test.print().c_str()),QString("9"));

    test /= 3;
    QCOMPARE(QString(test.print().c_str()),QString("3"));

    test = 2;
    test = test^3;
    QCOMPARE(QString(test.print().c_str()),QString("8"));

    test -= 4;
    QCOMPARE(QString(test.print().c_str()),QString("4"));

    test = Number(2,2,1);
    QCOMPARE(QString(test.print().c_str()),QString("[1.000000,1.000000,\n1.000000,1.000000,\n]"));

    test = test * 2;
    QCOMPARE(QString(test.print().c_str()),QString("[2.000000,2.000000,\n2.000000,2.000000,\n]"));

    std::vector<Numeric> array {2,2,3};

    test = Number(array);
    QCOMPARE(QString(test.print().c_str()),QString("[1.000000,2.000000,3.000000,\n]"));

}
