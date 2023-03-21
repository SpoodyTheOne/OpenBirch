#include "tst_number_arithmetics.h"
#include "base/expressionvalue.h"

#include <QTest>

void tst_number_arithmetics::RunNumberArithmetics()
{
    PreciseValue test;
    QCOMPARE(QString(test.get_str().c_str()),QString("0"));

    test = 1;
    QCOMPARE(QString(test.get_str().c_str()),QString("1"));

    test += 2;
    QCOMPARE(QString(test.get_str().c_str()),QString("3"));

    test *= test;
    QCOMPARE(QString(test.get_str().c_str()),QString("9"));

    test /= 3;
    QCOMPARE(QString(test.get_str().c_str()),QString("3"));

    test = 2;
    test = test^3;
    QCOMPARE(QString(test.get_str().c_str()),QString("8"));

    test -= 4;
    QCOMPARE(QString(test.get_str().c_str()),QString("4"));

    test = PreciseValue(2,2,1);
    QCOMPARE(QString(test.get_str().c_str()),QString("[1,1,\n1,1,\n]"));

    test = test * 2;
    QCOMPARE(QString(test.get_str().c_str()),QString("[2,2,\n2,2,\n]"));
}
