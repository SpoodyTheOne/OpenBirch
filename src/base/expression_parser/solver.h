#ifndef SOLVER_H
#define SOLVER_H

#include <QString>
#include <vector>
#include <string>

class Solver
{
public:
    Solver(QString);

    QString solve();
    void generateTree(bool runPostCompile = true);

private:
    QString preParse(QString);
    QString parse(QString);
    void compile(QString);
    void postCompile();
    QString evaluate();
    QString postEvaluate(QString);

private:
    std::vector<std::string> placeholders;
    QString infix;
    bool isTrueEquation;
};

#endif // SOLVER_H
