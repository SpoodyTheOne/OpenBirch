#include "number.h"
#include <iostream>

Number Number::operator+(Number other)
{
    if (isNaN || other.isNaN)
        return Number(0,true);

    return value + other.value;
}

Number Number::operator-(Number other)
{
    if (isNaN || other.isNaN)
        return Number(0,true);

    return value - other.value;
}

Number Number::operator*(Number other)
{
    if (isNaN || other.isNaN)
        return Number(0,true);

    return value * other.value;
}

Number Number::operator/(Number other)
{
    if (isNaN || other.isNaN)
        return Number(0,true);

    return value / other.value;
}

Number Number::operator^(Number other)
{
    mpfr_t out;
    mpfr_t a;
    mpfr_t b;

    mpfr_init_set_f(a, mpf_class(value).get_mpf_t(), MPFR_RNDN);
    mpfr_init_set_f(b, mpf_class(other.value).get_mpf_t(), MPFR_RNDN);

    mpfr_init(out);
    mpfr_pow(out, a, b, MPFR_RNDN);

    mpf_class r;
    mpfr_get_f(r.get_mpf_t(), out, MPFR_RNDN);



    return r;
}

bool Number::operator<=(Number other)
{
    if (isNaN || other.isNaN)
        return false;

    return value <= other.value;
}

bool Number::operator>=(Number other)
{
    if (isNaN || other.isNaN)
        return false;

    return value >= other.value;
}

bool Number::operator==(Number other)
{
    if (isNaN || other.isNaN)
        return isNaN == other.isNaN;

    return value == other.value;
}

bool Number::operator<(Number other)
{
    if (isNaN || other.isNaN)
        return false;

    return value < other.value;
}

bool Number::operator>(Number other)
{
    if (isNaN || other.isNaN)
        return false;

    return value > other.value;
}

bool Number::operator!=(Number other)
{
    if (isNaN || other.isNaN)
        return isNaN != other.isNaN;

    return value != other.value;
}


std::ostream& operator<<(std::ostream& os, const Number& n)
{
    os << n.value;
    return os;
}

std::string Number::toString(bool precise)
{
    std::cout << "is NaN: " << isNaN << std::endl;

    if (isNaN)
        return "NaN";

    if (precise)
        return Precise(value).get_str();

    std::ostringstream output_buffer;
    //output_buffer << value;
    return output_buffer.str();

}
