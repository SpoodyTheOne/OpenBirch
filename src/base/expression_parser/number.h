#ifndef NUMBER_H
#define NUMBER_H

#include <gmpxx.h>
#include <mpfr.h>
#include <sstream>

typedef mpq_class Precise;
typedef mpf_class Float;

class Number
{
public:
    static inline int FloatPrecision =          65536;
    static inline Precise PI =             Precise("167213075789791382630275400487886041651764456874403/53225575123090058458126718248444563466137046489291");
    static inline Precise EULER =          Precise("24262623368668294231481676215142722715775494156165/42033896243628889995829357765916572985978513879461");
    static inline Precise NATURAL_LOG =    Precise("335252563320801545640402003388958753787344419442826/123332525645750054058695631052085828318205458924797");

    Number() {};

    template<typename T>
    Number(T val, bool nan = false) : value(val, Number::FloatPrecision), isNaN(nan) {}

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
    Float value = 0;
    bool isNaN = false;
};

#endif // NUMBER_H
