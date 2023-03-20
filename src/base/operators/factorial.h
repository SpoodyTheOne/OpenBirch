#ifndef FACTORIAL_H
#define FACTORIAL_H

#include "operator.h"

class Factorial : public Operator
{
public:
    inline static const std::string name = "Factorial";
    inline static const std::string sign = "!";
    inline static const int predecence = 5;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }
    OperatorAssociativity getAssociativity() {return OperatorAssociativity::Right; }

    static Operator* create() { return new Factorial(); }

    ExpressionValue doOperation(std::vector<ExpressionValue> args)
    {
        assert(args.size() == argumentCount);

        ExpressionValue output = args[0];

        for (int i = args[0]-1; i >= 0; i--) {
            output *= args[0]-i;
        }

        return output;
    }
};

#endif // FACTORIAL_H
