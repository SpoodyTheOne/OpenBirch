#ifndef NEGATE_H
#define NEGATE_H

#include "operator.h"

class Negate : public Operator
{
public:
    inline static const std::string name = "Negate";
    inline static const std::string sign = "negate";
    inline static const int predecence = 4;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Negate(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return -args[0];
    }
};

#endif // NEGATE_H
