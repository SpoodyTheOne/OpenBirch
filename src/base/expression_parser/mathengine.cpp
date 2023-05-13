#include "base/expression_parser/mathengine.h"
#include "base/expression_parser/lexer/lexer.h"
#include "base/expression_parser/parser/parser.h"
#include "base/expression_parser/interpreter/interpreter.h"
#include "base/gmperror.h"
#include "base/openbirchstaticerror.h"

#include <QGuiApplication>
#include <QCursor>
#include <QWidget>

#include <future>
#include <chrono>
#include <cassert>

class MathLineEdit;

void MathEngine::AutoParse(QString input, Environment* globalEnvironment, std::function<void(MathOutput)> callback)
{
    using namespace std::chrono_literals;

    MathOutput output;

    QGuiApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

    try
    {
        Lexer lexer(input.toStdString());

        Parser parser = Parser(lexer.tokenize());

        std::vector<std::string> outputs;

        Interpreter interpreter(parser.parse(), globalEnvironment);

        #ifdef QT_NO_DEBUG
        auto promise = std::async(Interpreter::interpret, parser.parse(), globalEnvironment); //Interpreter::interpret(statements, globalEnvironment);

        std::future_status status;
        do {
            status = promise.wait_for(10ms);
            QCoreApplication::processEvents();
        } while (status != std::future_status::ready);

        outputs = promise.get();
        #else
        outputs = interpreter.interpret();
        #endif

        // Deallocate tokens and statements

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
    catch(GmpError e)
    {
        output.error = true;
        output.error_msg = e.what();
    }

    QGuiApplication::restoreOverrideCursor();

    callback(output);
}

void* MathEngine::Alloc(size_t size)
{
//    if (MathEngine::allocatedGmpMem + size > 1024*1024*1024)
//    {
//        throw GmpError("Result is greater than maximum allowed size (1gb)");
//    }
    MathEngine::allocatedGmpMem += size;
//    std::cout << "GMP MEM USAGE: " + std::to_string(MathEngine::allocatedGmpMem) << std::endl;
//    std::cout << "ALLOC: " + std::to_string(size) << std::endl;

    return malloc(size);
}


void* MathEngine::Realloc(void * ptr, size_t oldSize, size_t newSize)
{
//    if (MathEngine::allocatedGmpMem + newSize - oldSize > 1024*1024*1024)
//    {
//        throw GmpError("Result is greater than maximum allowed size (1gb)");
//    }

    MathEngine::allocatedGmpMem += newSize - oldSize;
//    std::cout << "REALLOC new: " + std::to_string(newSize) << std::endl;
//    std::cout << "REALLOC old: " + std::to_string(oldSize) << std::endl;
//    std::cout << "GMP MEM USAGE: " + std::to_string(MathEngine::allocatedGmpMem) << std::endl;

    return realloc(ptr, newSize);
}


void MathEngine::Free(void * mem, size_t size)
{
    free(mem);
    MathEngine::allocatedGmpMem -= size;
//    std::cout << "GMP MEM USAGE: " + std::to_string(MathEngine::allocatedGmpMem) << std::endl;
//    std::cout << "FREE: " + std::to_string(size) << std::endl;
}


void MathEngine::Init()
{
    // Set up GMP custom allocaters
    mp_set_memory_functions(&MathEngine::Alloc, &MathEngine::Realloc, &MathEngine::Free);
}










