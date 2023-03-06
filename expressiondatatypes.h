#ifndef EXPRESSIONDATATYPES_H
#define EXPRESSIONDATATYPES_H

#include <vector>
#include "typedef.h"

enum ExpressionDataType {
    number = 0,
    vector = 1,
    matrix = 2,
    list = 3
};

struct ExpressionData {
    std::vector<std::vector<T>> data;
    ExpressionDataType type;
};


#endif // EXPRESSIONDATATYPES_H
