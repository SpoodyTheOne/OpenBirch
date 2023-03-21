#ifndef ADDITION_H
#define ADDITION_H

#include "operator.h"

class Addition : public Operator
{
public:
    inline static const std::string name = "Addition";
    inline static const std::string sign = "+";
    inline static const int predecence = 2;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Addition(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return args[0] + args[1];
    }
};

#endif // ADDITION_H
