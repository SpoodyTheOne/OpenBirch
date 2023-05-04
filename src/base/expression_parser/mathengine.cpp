#include "base/expression_parser/mathengine.h"
#include "base/expression_parser/lexer/lexer.h"
#include "base/expression_parser/parser/parser.h"
#include "base/expression_parser/interpreter/interpreter.h"
#include "base/openbirchstaticerror.h"

#include <QGuiApplication>>
#include <QCursor>
#include <QWidget>

#include <future>
#include <chrono>

class MathLineEdit;

void MathEngine::AutoParse(QString input, Environment* globalEnvironment, std::function<void(MathOutput)> callback)
{
    using namespace std::chrono_literals;

    MathOutput output;

    QGuiApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

    try
    {
        Lexer lexer(input.toStdString());
        std::vector<Token *> tokens = lexer.tokenize();
        Parser parser = Parser(tokens);
        std::vector<Statement *> statements = parser.parse();

        auto promise = std::async(Interpreter::interpret, statements, globalEnvironment); //Interpreter::interpret(statements, globalEnvironment);

        std::future_status status;
        do {
            status = promise.wait_for(10ms);
            QCoreApplication::processEvents();
        } while (status != std::future_status::ready);

        std::vector<std::string> outputs = promise.get();

        // Deallocate tokens and statements
        std::vector<Token *>().swap(tokens);
        std::vector<Statement *>().swap(statements);

        std::string out = "";

        for (int i = 0; i < outputs.size(); i++)
        {
            out = out + outputs[i] + "\n";
        }

        // trim trailing comma
        output.output = out.substr(0,out.size()-1).c_str();

    } catch (OpenBirchStaticError e)
    {
        output.error = true;
        output.error_msg = e.what_better().c_str();
    }

    QGuiApplication::restoreOverrideCursor();

    callback(output);
}
