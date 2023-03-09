#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>
#include <vector>

typedef double Numeric;

class Number {
public:
    Number() {
        m_Value = std::vector<std::vector<Numeric>>{{}};
    }

    Number(Numeric values, ...) {
        m_Value = std::vector<std::vector<Numeric>>{{values}};
    }

    Number(int width, int height, Numeric default_value = 0) {
        m_Value = std::vector<std::vector<Numeric>>(width,std::vector<Numeric>(height,default_value));
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


    std::vector<std::vector<Numeric>> getRaw() {
        return m_Value;
    }

    Numeric operator()(int x, int y) {
        return m_Value[x][y];
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
