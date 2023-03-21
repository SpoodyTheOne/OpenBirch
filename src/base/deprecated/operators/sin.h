#ifndef SIN_H
#define SIN_H

#include "operator.h"

class Sinus : public Operator
{
public:
    inline static const std::string name = "Sine";
    inline static const std::string sign = "sin";
    inline static const int predecence = Precedence::Parenthesis;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Sinus(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return std::sin(args[0]);
    }
};


#endif // SIN_H
