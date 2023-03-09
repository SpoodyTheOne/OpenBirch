#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>
#include <string>
#include <vector>

typedef double Numeric;

class Number {
public:
    Number(Numeric input) {
        m_Value = std::vector<std::vector<Numeric>>{{input}};
    }

    Number(int width, int height, Numeric default_value = 0) {
        m_Value; std::vector<std::vector<Numeric>>()
    }

    Number operator+(Number input) {
        if (input.getWidth() != getWidth()) { // Vectors have a width > 1
            throw std::runtime_error("Tried to add Vectors or Matrices of different widths");
        } else if (input.getHeight() != getHeight()) { // 2d vector, aka matrix
            throw std::runtime_error("Tried to add Matrices of different widths");
        }

        Output =

        for (int i = 0; i < getHeight(); i++) {
            for (int x = 0; x < getWidth(); x++) {

            }
        }
    }

    int getWidth() {
        return m_Value[0].size();
    }

    int getHeight() {
        return m_Value.size();
    }
private:
    std::vector<std::vector<Numeric>> m_Value;
};

#endif // TYPES_H
