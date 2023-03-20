#ifndef ABS_H
#define ABS_H

#include "operator.h"

class Absolute : public Operator
{
public:
    inline static const std::string name = "Absolute";
    inline static const std::string sign = "abs";
    inline static const int predecence = Precedence::Parenthesis;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Absolute(); }

    ExpressionValue doOperation(std::vector<ExpressionValue> args)
    {
        assert(args.size() == argumentCount);
        return std::abs(args[0]);
    }
};


#endif // ABS_H
