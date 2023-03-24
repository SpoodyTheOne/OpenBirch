#ifndef SOLVER_H
#define SOLVER_H

#include <QString>
#include <vector>
#include <string>
#include "base/symboltable/symboltable.h"

class Solver
{
public:
    Solver(QString, SymbolTable *symboltable);

    QString solve();
    void generateTree(bool runPostCompile = true);

private:
    QString preParse(QString);
    QString parse(QString);
    /**
     * @brief Compiles a tree from the given postfix using a shunting yard algorithm
     */
    void compile(QString);
    void postCompile();
    QString evaluate();
    QString postEvaluate(QString);

private:
    std::vector<std::string> placeholders;
    QString infix;
    bool isTrueEquation;
    SymbolTable symbolTable;
    Node *compiledRoot = nullptr;
};

#endif // SOLVER_H
