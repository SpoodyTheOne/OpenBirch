#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <QString>

struct MathOutput
{
    bool error;
    QString error_msg;
    QString output;
};

class MathEngine
{
public:
    static QString AutoParse(QString);

    static QString Solve(QString);
    static QString Define(QString);
    static QString Calculate(QString);
};

#endif // MATHENGINE_H
