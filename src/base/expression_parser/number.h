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
    Number(T val) : value(InternalType(mpf_class(val))) {}

    Number operator+(Number);
    Number operator-(Number);
    Number operator*(Number);
    Number operator/(Number);
    Number operator^(Number);

    friend std::ostream& operator<<(std::ostream& os, const Number& n);

    std::string toString();
    std::string toUserString();

private:
    InternalType value;
};

#endif // NUMBER_H
