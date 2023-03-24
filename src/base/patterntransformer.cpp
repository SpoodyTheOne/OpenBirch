#include "patterntransformer.h"

QString PatternTransformer::Transform(QString pattern, QString change, QString input)
{
    QString output = input;

    for (size_t i = 0; i < Patterns.size(); i++)
    {
        pattern = pattern.replace(QRegExp(Patterns[i]),Regexes[i]);
    }

    QRegularExpressionMatchIterator it = QRegularExpression(pattern).globalMatch(input);

    while (it.hasNext())
    {
        // an instance of the pattern in the string
        QString match = it.next().captured();

        // surround all "variables" in the string with $...\$
        for (size_t i = 0; i < Regexes.size(); i++)
        {
            QRegularExpressionMatchIterator RegIt = QRegularExpression(Regexes[i]).globalMatch(match);
            while (RegIt.hasNext())
            {
                auto m = RegIt.next();
                match.replace(m.captured(),"$" + m.captured() + "\\$");
            }
        }

        QRegularExpressionMatchIterator FinalIt = QRegularExpression("$.+\\$").globalMatch(match);

        QString replacer = change;

        int i = 0;
        while (FinalIt.hasNext())
        {
            auto m = FinalIt.next();

            QString value = m.captured().mid(1,-3); // remove first char and last 2 char

            replacer.replace("$" + QString(i), value);
        }

        output.replace(match,replacer);
    }

    return output;
}
