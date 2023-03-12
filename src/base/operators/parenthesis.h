#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "operator.h"

class LParenthesis : public Operator
{
public:
    inline static const std::string name = "Left Parenthesis";
    inline static const std::string sign = "(";
    inline static const int predecence = 5;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new LParenthesis(); }
};

class RParenthesis : public Operator
{
public:
    inline static const std::string name = "Right Parenthesis";
    inline static const std::string sign = ")";
    inline static const int predecence = 5;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }

    static Operator* create() { return new RParenthesis(); }
};

#endif // PARENTHESIS_H
