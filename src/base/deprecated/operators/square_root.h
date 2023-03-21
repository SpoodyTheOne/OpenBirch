#ifndef SQUARE_ROOT_H
#define SQUARE_ROOT_H

#include "operator.h"

class Square_Root : public Operator
{
public:
    inline static const std::string name = "Square Root";
    inline static const std::string sign = "sqrt";
    inline static const int predecence = Precedence::Parenthesis;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Square_Root(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return std::sqrt(args[0]);
    }
};


#endif // SQUARE_ROOT_H
