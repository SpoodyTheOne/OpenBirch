#include "base/expression_parser/mathengine.h"

void MathEngine::AutoParse(QString input, SymbolTable *table, qstringcallback callback)
{
    Solver solver(input, table);

    MathOutput output;

    try
    {
        output.output = solver.solve();
    } catch (std::runtime_error e)
    {
        output.error = true;
        output.error_msg = e.what();
    }

    callback(output);
}
