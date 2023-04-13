#include "number.h"

Number Number::operator=(Number other)
{
    return other;
}

Number Number::operator+(Number other)
{
    return value + other.value;
}

Number Number::operator-(Number other)
{
    return value - other.value;
}

Number Number::operator*(Number other)
{
    return value * other.value;
}

Number Number::operator/(Number other)
{
    return value / other.value;
}

Number Number::operator^(Number other)
{
    return
}
