#include <QTest>
#include "tst_expression_result.h"
#include "tst_number_arithmetics.h"
#include "tst_postfix_convert.h"

int main(int argc, char *argv[])
{
    // See https://alexhuszagh.github.io/2016/using-qttest-effectively/
    int status = 0;
    status |= QTest::qExec(new tst_number_arithmetics, argc, argv);
    status |= QTest::qExec(new tst_postfix_convert, argc, argv);
    status |= QTest::qExec(new tst_expression_result, argc, argv);
    return status;
}
