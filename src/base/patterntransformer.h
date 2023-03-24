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

    static inline std::vector<QRegExp> Patterns
    {
        QRegExp("$n"),    // Number
        QRegExp("$$"),      // Anything
    };
    static inline std::vector<QRegExp> Regexes
    {
        QRegExp("(\\d*((?<!\\.)\\.)?\\d)"), // Number
        QRegExp(".*"),                      // Anything
    };
};

#endif // PATTERNTRANSFORMER_H
