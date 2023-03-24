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
        "$n",    // Number
        "$$",      // Anything
    };
    static inline std::vector<QString> Regexes
    {
        "(\\d*((?<!\\.)\\.)?\\d)", // Number
        ".*",                      // Anything
    };
};

#endif // PATTERNTRANSFORMER_H