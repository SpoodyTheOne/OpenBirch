#ifndef VARIABLE_H
#define VARIABLE_H

#include <gmpxx.h>
#include <vector>

namespace BirchLang {

enum VariableType {
    Number,
    String,
    Function, // TODO
    Vector,
    Matrix
};

class Variable
{
public:
    Variable();
    Variable(mpq_class);
    Variable(std::string);
    Variable(std::vector<Variable>);
    Variable(std::vector<std::vector<Variable>>);

    mpq_class getNumberValue();
    std::string getStringValue();
    std::vector<Variable> getVectorValue();
    std::vector<std::vector<Variable>> getMatrixValue();

    VariableType type;

    Variable operator+(Variable other) {

        if (other.type == VariableType::Number && this->type == VariableType::Number)
            return Variable(this->getNumberValue() + other.getNumberValue());

        if (other.type == VariableType::String && this->type == VariableType::String)
            return Variable(this->getStringValue() + other.getStringValue());


        if (other.type == VariableType::Vector && this->type == VariableType::Vector)
        {
            int thisSize = this->getVectorValue().size();

            if (thisSize == other.getVectorValue().size())
            {
            for (int i = 0; i < thisSize; i++)
                {

                }
            }
        }

        throw new std::runtime_error("Cant do this");
    }

private:
    mpq_class NumberValue;
    std::string StringValue;
    std::vector<Variable> VectorValue;
    std::vector<std::vector<Variable>> MatrixValue;
};

}
#endif // VARIABLE_H
