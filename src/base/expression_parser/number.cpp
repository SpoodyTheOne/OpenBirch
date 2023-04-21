#include "number.h"

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
    mpfr_t out;
    mpfr_t a;
    mpfr_t b;

    mpfr_init_set_f(a, mpf_class(value).get_mpf_t(), MPFR_RNDN);
    mpfr_init_set_f(b, mpf_class(other.value).get_mpf_t(), MPFR_RNDN);

    mpfr_init(out);
    mpfr_pow(out, a, b, MPFR_RNDN);

    mpf_class r;
    mpfr_get_f(r.get_mpf_t(), out, MPFR_RNDN);


    return mpf_class(r, Number::FloatPrecision);
}

bool Number::operator<=(Number other)
{
    return value <= other.value;
}

bool Number::operator>=(Number other)
{
    return value >= other.value;
}

bool Number::operator==(Number other)
{
    return value == other.value;
}

bool Number::operator<(Number other)
{
    return value < other.value;
}

bool Number::operator>(Number other)
{
    return value > other.value;
}

bool Number::operator!=(Number other)
{
    return value != other.value;
}


std::ostream& operator<<(std::ostream& os, const Number& n)
{
    os << n.value;
    return os;
}

std::string Number::toString(bool precise)
{
    if (precise)
        return value.get_str();

    std::ostringstream output_buffer;
    output_buffer << mpf_class(value, Number::FloatPrecision);
    return output_buffer.str();
}
