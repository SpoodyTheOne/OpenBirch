#include "operatorfactory.h"
#include "multiply.h"
#include "division.h"
#include "addition.h"
#include "subtraction.h"
#include "parenthesis.h"
#include "exponent.h"
#include "equals.h"
#include "negate.h"
#include <algorithm>
#include <iostream>

OperatorLookupTable::OperatorLookupTable()
{
    // Register lookup table. Corresponding signs 2 concrete operator factory method
    this->registerOp("*", &Multiply::create);
    this->registerOp("/", &Division::create);
    this->registerOp("+", &Addition::create);
    this->registerOp("-", &Subtraction::create);
    this->registerOp("(", &LParenthesis::create);
    this->registerOp(")", &RParenthesis::create);
    this->registerOp("^", &Exponent::create);
    this->registerOp("=", &Equals::create);
    this->registerOp("negate", &Negate::create);
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
    // Uncomment to make case-insensitive
    //std::transform(sign.begin(), sign.end(), sign.begin(),
    //[](unsigned char c){ return std::tolower(c); });

    std::unordered_map<std::string, CreateOperatorFn>::iterator it = lookupTable.lookupMap.find(sign);
    if (it != lookupTable.lookupMap.end())
        return it->second();
    return nullptr;
}

bool OperatorFactory::IsOperator(std::string input) {
    // https://stackoverflow.com/a/11765524
    return lookupTable.lookupMap.count(input);
}
