#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "operator.h"

class Subtraction : public Operator
{
public:
    inline static const std::string name = "Subtraction";
    inline static const std::string sign = "-";
    inline static const int predecence = 2;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Subtraction(); }

    ExpressionValue doOperation(std::vector<ExpressionValue> args)
    {
        assert(args.size() == argumentCount);
        return args[1] - args[0];
    }
};

#endif // SUBTRACTION_H
