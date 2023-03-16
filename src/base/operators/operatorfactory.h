#ifndef OPERATORFACTORY_H
#define OPERATORFACTORY_H

#include "base/operators/operator.h"
#include <unordered_map>
#include <string>
typedef Operator* (*CreateOperatorFn)();

class OperatorLookupTable
{
public:
    OperatorLookupTable();
    ~OperatorLookupTable();
    void registerOp(std::string sign, CreateOperatorFn createOperatorFn);

    friend class OperatorFactory;
private:
    std::unordered_map<std::string, CreateOperatorFn> lookupMap;
};

class OperatorFactory
{
public:
    OperatorFactory();
    static Operator* create(std::string sign);

    static bool IsOperator(std::string);

private:
    inline static OperatorLookupTable lookupTable;
};

#endif // OPERATORFACTORY_H
