#ifndef COS_H
#define COS_H

#include "operator.h"

class Cosine : public Operator
{
public:
    inline static const std::string name = "Cosine";
    inline static const std::string sign = "cos";
    inline static const int predecence = Precedence::Parenthesis;
    inline static const int argumentCount = 1;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Cosine(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);
        return std::cos(args[0]);
    }
};


#endif // COS_H
