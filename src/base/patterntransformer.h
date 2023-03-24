#ifndef PATTERNTRANSFORMER_H
#define PATTERNTRANSFORMER_H

#include <QRegExp>
#include <QString>
#include <unordered_map>
#include <vector>
#include <QRegularExpression>

class PatternTransformer
{
public:
    static QString Transform(QString, QString, QString);

    static inline QRegularExpression placeholder = QRegularExpression("$.");

    static inline std::vector<QString> Patterns
    {
        "\\$n",     // Number
        "\\$v",     //Variable
        "\\$\\$",   // Anything
    };
    static inline std::vector<QString> Regexes
    {
        "([1-9]\\d*(?:\\.\\d+)?)",    // Number
        "([^\\d\\W]_?_?[\\w]*)",
        "([\\S\\s]*)",              // Anything
    };
};

#endif // PATTERNTRANSFORMER_H
