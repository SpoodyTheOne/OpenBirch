#include "solver.h"

Solver::Solver(QString input)
{
    this->infix = input;
}

QString Solver::solve()
{
    QString preParsed = preParse(infix);
    QString parsed = parse(preParsed);

    compile(parsed);
    postCompile();

    QString evaluated = evaluate();
    QString postEvaluated = postEvaluate(evaluated);

    return postEvaluated;
}

QString Solver::preParse(QString input)
{
    // Replace aliases of operators with their true sign ( cdot -> *)

    // Replace functions with placeholders

    // Use symboltable to automatically turn 2x -> 2*x or xy -> x*y
}

QString Solver::parse(QString input)
{

}

void Solver::compile(QString postfix)
{

}

void Solver::postCompile()
{

}

QString Solver::evaluate()
{

}

QString postEvaluate(QString input)
{

}
