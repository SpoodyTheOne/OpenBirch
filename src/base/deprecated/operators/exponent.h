#ifndef EXPONENT_H
#define EXPONENT_H

#include "operator.h"

class Exponent : public Operator
{
public:
    inline static const std::string name = "Exponent";
    inline static const std::string sign = "^";
    inline static const int predecence = 5;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }
    OperatorAssociativity getAssociativity() {return OperatorAssociativity::Right; }

    static Operator* create() { return new Exponent(); }

    ExpressionValue doOperation(std::vector<ExpressionValue> args)
    {
        assert(args.size() == argumentCount);
        return std::pow(args[0],args[1]);
    }
};


#endif // EXPONENT_H
