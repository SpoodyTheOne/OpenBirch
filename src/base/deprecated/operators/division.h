#ifndef DIVISION_H
#define DIVISION_H

#include "operator.h"

class Division : public Operator
{
public:
    inline static const std::string name = "Division";
    inline static const std::string sign = "/";
    inline static const int predecence = 3;
    inline static const int argumentCount = 2;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Division(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return args[0] / args[1];
    }
};

#endif // DIVISION_H
