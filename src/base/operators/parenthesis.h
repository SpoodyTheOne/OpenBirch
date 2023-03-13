#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "operator.h"

class LParenthesis : public Operator
{
public:
    inline static const std::string name = "Left Parenthesis";
    inline static const std::string sign = "(";
    inline static const int predecence = 5;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new LParenthesis(); }

    Number doOperation(Number a, Number b) { return 0; }
};

class RParenthesis : public Operator
{
public:
    inline static const std::string name = "Right Parenthesis";
    inline static const std::string sign = ")";
    inline static const int predecence = 5;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new RParenthesis(); }

    Number doOperation(Number a, Number b) { return 0; }
};

#endif // PARENTHESIS_H
