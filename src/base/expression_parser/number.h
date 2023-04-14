#ifndef NUMBER_H
#define NUMBER_H

#include <gmpxx.h>
#include <mpfr.h>

typedef mpq_class InternalType;

class Number
{
public:
    Number() { value = 0; };

    template<typename T>
    Number(T val) : value(val) {}

    Number operator+(Number);
    Number operator-(Number);
    Number operator*(Number);
    Number operator/(Number);
    Number operator^(Number);

private:
    InternalType value;
};

#endif // NUMBER_H
