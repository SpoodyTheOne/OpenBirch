#ifndef SUM_H
#define SUM_H

#include "base/deprecated/expression_parser/variablenode.h"
#include "operator.h"

class Sum : public Operator
{
public:
    inline static const std::string name = "Sum";
    inline static const std::string sign = "sum";
    inline static const int predecence = Precedence::Parenthesis;
    inline static const int argumentCount = 4;

    std::string getName() { return name; }
    std::string getSign() { return sign; }
    int getPredecence() { return predecence; }
    int getArgumentCount() { return argumentCount; }

    static Operator* create() { return new Sum(); }

    PreciseValue doOperation(std::vector<PreciseValue> args)
    {
        assert(args.size() == argumentCount);

        return args[0] + args[1] + args[2] + args[3];
    }
};


#endif // SUM_H
