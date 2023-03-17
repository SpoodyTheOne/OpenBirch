#ifndef TST_EXPRESSION_RESULT_H
#define TST_EXPRESSION_RESULT_H

#include <QObject>

class tst_expression_result : public QObject
{
    Q_OBJECT

private slots:
    void RunAdditionTests();
    void RunSubtractionTests();
    void RunMultiplicationTests();
    void RunDivisionTests();
    void RunExponentTests();
    void RunBasicPrecedenceTests();
    void RunNegateTests();
};

#endif // TST_EXPRESSION_RESULT_H
