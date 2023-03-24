#include "patterntransformer.h"

QString PatternTransformer::Transform(QString pattern, QString change, QString input)
{
    QString output = input;

    for (size_t i = 0; i < Patterns.size(); i++)
    {
        pattern = pattern.replace(Patterns[i],Regexes[i].pattern());
    }

    QRegularExpressionMatchIterator it = QRegularExpression(pattern).globalMatch(input);

    while (it.hasNext())
    {
        std::vector<std::string> placeholders;
        QRegularExpressionMatch match = it.next();
    }


}
