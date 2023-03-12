#ifndef TST_POSTFIX_CONVERT_H
#define TST_POSTFIX_CONVERT_H

#include <QObject>

class tst_postfix_convert : public QObject
{
    Q_OBJECT

private slots:
    void RunSimple();
    void RunMultipleTerms();
    void RunPrecedenceOrder();
    void RunWithParenthesis();
};

#endif // TST_POSTFIX_CONVERT_H
