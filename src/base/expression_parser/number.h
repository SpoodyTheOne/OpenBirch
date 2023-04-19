#ifndef NUMBER_H
#define NUMBER_H

#include <gmpxx.h>
#include <mpfr.h>
#include <sstream>

typedef mpq_class InternalType;

class Number
{
public:
    static inline int FloatPrecision = 65565;

    Number() { value = 0; };

    template<typename T>
    Number(T val) : value(InternalType(mpf_class(val, Number::FloatPrecision))) {}

    Number operator+(Number);
    Number operator-(Number);
    Number operator*(Number);
    Number operator/(Number);
    Number operator^(Number);

    bool operator<=(Number);
    bool operator>=(Number);
    bool operator==(Number);
    bool operator<(Number);
    bool operator>(Number);
    bool operator!=(Number);

    friend std::ostream& operator<<(std::ostream& os, const Number& n);

    std::string toString();

private:
    InternalType value;
};

#endif // NUMBER_H
