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
        std::vector<Statement *> statements = parser.parse();

        std::vector<std::string> outputs = Interpreter::interpret(statements);

        // Deallocate tokens and statements
        std::vector<Token *>().swap(tokens);
        std::vector<Statement *>().swap(statements);

        std::string out = "";

        for (std::string s : outputs)
        {
            out = out + s + "\n";
        }

        // trim trailing comma
        output.output = out.substr(0,out.size()-2).c_str();

    } catch (OpenBirchStaticError e)
    {
        output.error = true;
        output.error_msg = e.what_better().c_str();
    }

    callback(output);
}
