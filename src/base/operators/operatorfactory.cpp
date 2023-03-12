#include "operatorfactory.h"
#include "multiply.h"
#include "division.h"
#include "addition.h"
#include "subtraction.h"
#include "parenthesis.h"

OperatorLookupTable::OperatorLookupTable()
{
    // Register lookup table. Corresponding signs 2 concrete operator factory method
    this->registerOp("*", &Multiply::create);
    this->registerOp("/", &Division::create);
    this->registerOp("+", &Addition::create);
    this->registerOp("-", &Subtraction::create);
    this->registerOp("(", &LParenthesis::create);
    this->registerOp(")", &RParenthesis::create);
}

void OperatorLookupTable::registerOp(std::string sign, CreateOperatorFn createOperatorFn)
{
    this->lookupMap.insert_or_assign(sign, createOperatorFn);
}

OperatorLookupTable::~OperatorLookupTable()
{
    this->lookupMap.clear();
}

OperatorFactory::OperatorFactory()
{

}

Operator* OperatorFactory::create(std::string sign)
{
    std::map<std::string, CreateOperatorFn>::iterator it = lookupTable.lookupMap.find(sign);
    if (it != lookupTable.lookupMap.end())
        return it->second();
    return nullptr;
}
