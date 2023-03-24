#include "base/expression_parser/mathengine.h"

class MathLineEdit;

void MathEngine::AutoParse(QString input, SymbolTable *table, std::function<void(MathOutput)> callback)
{
    SymbolMap *map = table->getMap();
    SymbolMap *newMap = SymbolTable().getMap();

    newMap->size();
    map->size();

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
