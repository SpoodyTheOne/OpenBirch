#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <QString>
#include "base/expression_parser/solver.h"

struct MathOutput
{
    bool error;
    QString error_msg;
    QString output;
};

typedef void(*qstringcallback)(MathOutput);

class MathEngine
{
public:
    static void AutoParse(QString, SymbolTable*, qstringcallback);

    static MathOutput Solve(QString);
    static MathOutput Define(QString);
    static MathOutput Calculate(QString);
};

#endif // MATHENGINE_H
