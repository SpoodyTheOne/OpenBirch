#ifndef TST_EXPRESSION_RESULT_H
#define TST_EXPRESSION_RESULT_H

#include <QObject>
#include "base/expression_parser/deprecated/expressionparser.h"

class tst_expression_result : public QObject
{
    Q_OBJECT
private:

private slots:
    void RunAdditionTests();
};

#endif // TST_EXPRESSION_RESULT_H
