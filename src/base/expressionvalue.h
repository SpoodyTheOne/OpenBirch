#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>
#include <sstream>
#include <QString>

typedef mpq_class Numeric;
#define float_precision 16384
#define scientific_conversion_cutoff 1000000

static inline std::string NumericToString(Numeric num) {
    if (num > 0) {
        std::ostringstream output_buffer;
        output_buffer << mpf_class(num,float_precision);
        return output_buffer.str();
    }

    auto str = num.get_str();
    return str;
}

class PreciseValue {
public:
    PreciseValue() {
        m_Value = std::vector<std::vector<Numeric>>{{mpq_class(0)}};
    }

    template<typename T>
    PreciseValue(T value)
    {
        m_Value = std::vector<std::vector<Numeric>>{{mpq_class(mpf_class(value,float_precision))}};
    }

    template<typename T>
    PreciseValue(int width, int height, T default_value = 0) {
        m_Value = std::vector<std::vector<Numeric>>(width,std::vector<Numeric>(height,mpq_class(mpf_class(default_value,float_precision))));
    }

    PreciseValue(std::vector<Numeric> value) {
        m_Value = std::vector<std::vector<Numeric>>{value};
    }


    std::string get_str() {
        std::string output = "[";

        int height = getHeight();

        if (height == 0)
            return "[]";

        int width = getWidth();

        if (isSingular())
            return NumericToString((*this)(0,0));

        for (int i = 0; i < width; i++) {
            for (int x = 0; x < height; x++) {
                output = output + NumericToString((*this)(0,0)) + ",";
            }
            output = output + "\n";
        }

        output = output + "]";

        return output;
    }

    std::vector<std::vector<Numeric>> getRaw() {
        return m_Value;
    }

    Numeric operator()(int x, int y) {
        return m_Value[x][y];
    }

    template<typename T>
    void operator=(T value) {
        if (getWidth() == 1 && getHeight() == 1)
            m_Value[0][0] = value;
        else
            throw std::runtime_error("Cant assign number to Vector/Matrix");
    }

    template<typename T>
    PreciseValue operator*(T input) {
        int width = getWidth();
        int height = getHeight();
        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,((*this)(i,x))*input);
            }
        }

        return Output;
    }

    PreciseValue operator*(PreciseValue input) {
        int width = getWidth();
        int height = getHeight();

        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to multiply Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to multiply Matrices of different widths");
        }

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,(*this)(i,x)*input(i,x));
            }
        }

        return Output;
    }

    void operator*=(PreciseValue input) {
        this->m_Value = ((*this)*input).m_Value;
    }

    template<typename T>
    void operator*=(T input) {
        this->m_Value = ((*this)*input).m_Value;
    }

    template<typename T>
    PreciseValue operator/(T input) {
        return (*this)*mpq_class(1,input);
    }

    PreciseValue operator/(PreciseValue input) {
        int width = getWidth();
        int height = getHeight();

        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to divide Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to divide Matrices of different widths");
        }

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,(*this)(i,x)/input(i,x));
            }
        }

        return Output;
    }

    void operator/=(PreciseValue input) {
        this->m_Value = ((*this)/input).m_Value;
    }

    template<typename T>
    void operator/=(T input) {
        this->m_Value = ((*this)/input).m_Value;
    }

    PreciseValue operator+(PreciseValue input) {
        int width = getWidth();
        int height = getHeight();
        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
                Output.setRaw(i,x,input(i,x) + (*this)(i,x));
            }
        }

        return Output;
    }

    template<typename T>
    PreciseValue operator+(T input) {
        int width = getWidth();
        int height = getHeight();

        if (width != 1 || height != 1)
            throw std::runtime_error("Cannot add a number to a Vector/Matrix");

        PreciseValue Output = PreciseValue(width,height, 0);

        Output.setRaw(0,0,(*this)(0,0) + input);

        return Output;
    }

    template<typename T>
    void operator+=(T value) {
        m_Value = ((*this)+value).m_Value;
    }

    void operator+=(PreciseValue value) {
        m_Value = ((*this)+value).m_Value;
    }

    PreciseValue operator-(PreciseValue input) {
        int width = getWidth();
        int height = getHeight();
        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
                Output.setRaw(i,x,input(i,x) - (*this)(i,x));
            }
        }

        return Output;
    }

    template<typename T>
    PreciseValue operator-(T input) {
        int width = getWidth();
        int height = getHeight();

        if (width != 1 || height != 1)
            throw std::runtime_error("Cannot add a number to a Vector/Matrix");

        PreciseValue Output = PreciseValue(width,height, 0);

        Output.setRaw(0,0,(*this)(0,0) - input);

        return Output;
    }

    template<typename T>
    void operator-=(T value) {
        m_Value = ((*this)-value).m_Value;
    }

    void operator-=(PreciseValue value) {
        m_Value = ((*this)-value).m_Value;
    }

    PreciseValue operator^(PreciseValue input) {
        int width = getWidth();
        int height = getHeight();
        if (!input.isSingular())
            throw std::runtime_error("Cannot use a Vector/Matrix as an exponent");

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {

                Numeric value = pow((*this)(i,x).get_d(),input(0,0).get_d());

                Output.setRaw(i,x,value);
            }
        }

        return Output;
    }

    template<typename T>
    PreciseValue operator^(T input) {
        int width = getWidth();
        int height = getHeight();

        PreciseValue Output = PreciseValue(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {

                Numeric value = pow((*this)(i,x).get_d(),input);

                Output.setRaw(i,x,value);
            }
        }

        return Output;
    }

    operator double() const {
        return m_Value[0][0].get_d();
    }

    operator QString() const {
        return m_Value[0][0].get_str().c_str();
    }

    int getWidth() {
        return m_Value[0].size();
    }

    int getHeight() {
        return m_Value.size();
    }

    void setRaw(int x, int y, Numeric value) {
        m_Value[x][y] = value;
    }

    bool isValid() {
        return this->getHeight() > 0 && this->getWidth() > 0;
    }

    bool isSingular() {
        return (this->getWidth() == 1 && this->getHeight() == 1);
    }
private:
    std::vector<std::vector<Numeric>> m_Value;
};

#endif // TYPES_H
