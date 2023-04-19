#include "base/expression_parser/mathengine.h"
#include "base/expression_parser/lexer/lexer.h"
#include "base/expression_parser/parser/parser.h"
#include "base/expression_parser/interpreter/interpreter.h"
#include "base/openbirchstaticerror.h"

class MathLineEdit;

void MathEngine::AutoParse(QString input, SymbolTable *table, std::function<void(MathOutput)> callback)
{
    MathOutput output;

    try
    {
        Lexer lexer(input.toStdString());
        std::vector<Token *> tokens = lexer.tokenize();
        Parser parser = Parser(tokens);
        Expression* expr = parser.parse();

        output.output = QString(Interpreter::interpret(expr).c_str());

        for (Token* t : tokens)
        {
            delete t;
        }

        delete expr;
    } catch (OpenBirchStaticError e)
    {
        output.error = true;
        output.error_msg = e.what();
    }

    callback(output);
}
