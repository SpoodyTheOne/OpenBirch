#include "patterntransformer.h"

QString PatternTransformer::Transform(QString pattern, QString change, QString input)
{
    for (size_t i = 0; i < Patterns.size(); i++)
    {
        auto p = QRegularExpression(Patterns[i]);
        pattern = pattern.replace(p,Regexes[i]);
    }

    change = change.replace(QRegularExpression("\\$(\\d)"),"\\\\1");

    QString output = input.replace(QRegularExpression(pattern),change);

    return output;
}
