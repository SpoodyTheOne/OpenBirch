#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

typedef double Numeric;

class Number {
public:
    Number() {
        m_Value = std::vector<std::vector<Numeric>>{{0}};
    }

    Number(Numeric value) {
        m_Value = std::vector<std::vector<Numeric>>{{value}};
    }

    Number(int width, int height, Numeric default_value = 0) {
        m_Value = std::vector<std::vector<Numeric>>(width,std::vector<Numeric>(height,default_value));
    }

    Number(std::vector<Numeric> value) {
        m_Value = std::vector<std::vector<Numeric>>{value};
    }


    std::string print() {
        std::string output = "[";

        int width = getWidth();
        int height = getHeight();

        if (isSingular()) {
            auto str = std::to_string((*this)(0,0));
            str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
            str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
            return str;
        }

        for (int i = 0; i < width; i++) {
            for (int x = 0; x < height; x++) {
                output = output + std::to_string((*this)(i,x)) + ",";
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

    void operator=(Numeric value) {
        if (getWidth() == 1 && getHeight() == 1)
            m_Value[0][0] = value;
        else
            throw std::runtime_error("Cant assign number to Vector/Matrix");
    }

    Number operator*(Numeric input) {
        int width = getWidth();
        int height = getHeight();
        Number Output = Number(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,(*this)(i,x)*input);
            }
        }

        return Output;
    }

    Number operator*(Number input) {
        int width = getWidth();
        int height = getHeight();

        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to multiply Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to multiply Matrices of different widths");
        }

        Number Output = Number(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,(*this)(i,x)*input(i,x));
            }
        }

        return Output;
    }

    void operator*=(Number input) {
        this->m_Value = ((*this)*input).m_Value;
    }

    void operator*=(Numeric input) {
        this->m_Value = ((*this)*input).m_Value;
    }

    Number operator/(Numeric input) {
        return (*this)*(1/input);
    }

    Number operator/(Number input) {
        int width = getWidth();
        int height = getHeight();

        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to divide Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to divide Matrices of different widths");
        }

        Number Output = Number(width,height, 0);

        for (int i = 0; i < height; i++) {
            for (int x = 0; x < width; x++) {
                Output.setRaw(i,x,(*this)(i,x)/input(i,x));
            }
        }

        return Output;
    }

    void operator/=(Number input) {
        this->m_Value = ((*this)/input).m_Value;
    }

    void operator/=(Numeric input) {
        this->m_Value = ((*this)/input).m_Value;
    }

    Number operator+(Number input) {
        int width = getWidth();
        int height = getHeight();
        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        Number Output = Number(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
                Output.setRaw(i,x,input(i,x) + (*this)(i,x));
            }
        }

        return Output;
    }

    Number operator+(Numeric input) {
        int width = getWidth();
        int height = getHeight();

        if (width != 1 || height != 1)
            throw std::runtime_error("Cannot add a number to a Vector/Matrix");

        Number Output = Number(width,height, 0);

        Output.setRaw(0,0,(*this)(0,0) + input);

        return Output;
    }

    void operator+=(Numeric value) {
        m_Value = ((*this)+value).m_Value;
    }

    void operator+=(Number value) {
        m_Value = ((*this)+value).m_Value;
    }

    Number operator-(Number input) {
        int width = getWidth();
        int height = getHeight();
        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        Number Output = Number(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
                Output.setRaw(i,x,input(i,x) - (*this)(i,x));
            }
        }

        return Output;
    }

    Number operator-(Numeric input) {
        int width = getWidth();
        int height = getHeight();

        if (width != 1 || height != 1)
            throw std::runtime_error("Cannot add a number to a Vector/Matrix");

        Number Output = Number(width,height, 0);

        Output.setRaw(0,0,(*this)(0,0) - input);

        return Output;
    }

    void operator-=(Numeric value) {
        m_Value = ((*this)-value).m_Value;
    }

    void operator-=(Number value) {
        m_Value = ((*this)-value).m_Value;
    }

    Number operator^(Number input) {
        int width = getWidth();
        int height = getHeight();
        if (!input.isSingular())
            throw std::runtime_error("Cannot use a Vector/Matrix as an exponent");

        Number Output = Number(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {

                Numeric value = pow((*this)(i,x), input(0,0));

                Output.setRaw(i,x,value);
            }
        }

        return Output;
    }

    Number operator^(Numeric input) {
        int width = getWidth();
        int height = getHeight();

        Number Output = Number(width,height, 0);

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {

                Numeric value = pow((*this)(i,x), input);

                Output.setRaw(i,x,value);
            }
        }

        return Output;
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

    bool isSingular() {
        return (this->getWidth() == 1 && this->getHeight() == 1);
    }
private:
    std::vector<std::vector<Numeric>> m_Value;
};

#endif // TYPES_H
