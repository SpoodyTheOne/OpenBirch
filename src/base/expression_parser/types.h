#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>
#include <vector>

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




    std::string print() {
        std::string output = "[";

        int width = getWidth();
        int height = getHeight();

        if (width == 1 && height == 1) {
            auto str = std::to_string((*this)(0,0));
            str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
            str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
            return str;
        }

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
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


    void operator+=(Numeric value) {
        if (getWidth() == 1 && getHeight() == 1)
            m_Value[0][0] += value;
        else
            throw std::runtime_error("Cant add number to Vector/Matrix");
    }

    void operator-=(Numeric value) {
        if (getWidth() == 1 && getHeight() == 1)
            m_Value[0][0] -= value;
        else
            throw std::runtime_error("Cant subtract number to Vector/Matrix");
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

    Number operator+(Number input) {
        int width = getWidth();
        int height = getHeight();
        if (input.getWidth() != width) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != height) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        Number Output = Number(width,height, 0);

        Number this_value = *this;

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {
                Output.setRaw(i,x,input(i,x) + this_value(i,x));
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
private:
    std::vector<std::vector<Numeric>> m_Value;
};

#endif // TYPES_H
