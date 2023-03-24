#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <QString>
#include <functional>
#include "base/expression_parser/solver.h"

class MathEditLine;

struct MathOutput
{
    bool error = false;
    QString error_msg;
    QString output;
};

class MathEngine
{
public:
    /**
     * @brief Automatically tries to figure out what to do with the input string.
     * @param The input string
     * @param SymbolTable for variables and such
     * @param Callback function, returns a MathOutput
     */
    static void AutoParse(QString, SymbolTable const&, std::function<void(MathOutput)>);

    static MathOutput Solve(QString);
    static MathOutput Define(QString);
    static MathOutput Calculate(QString);
};

#endif // MATHENGINE_H
