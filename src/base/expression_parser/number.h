#ifndef NUMBER_H
#define NUMBER_H

#include <gmpxx.h>
#include <mpfr.h>
#include <sstream>

typedef mpq_class InternalType;

class Number
{
public:
    static inline int FloatPrecision =          65536;
    static inline InternalType PI =             InternalType("167213075789791382630275400487886041651764456874403/53225575123090058458126718248444563466137046489291");
    static inline InternalType EULER =          InternalType("24262623368668294231481676215142722715775494156165/42033896243628889995829357765916572985978513879461");
    static inline InternalType NATURAL_LOG =    InternalType("335252563320801545640402003388958753787344419442826/123332525645750054058695631052085828318205458924797");

    Number() {};
    Number(bool isNaN) : isNaN(isNaN) {};

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

    std::string toString(bool precise = false);

private:
    InternalType value = 0;
    bool isNaN = false;
};

#endif // NUMBER_H
