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
            unsigned long size = std::max(this->getVectorValue().size(),other.getVectorValue().size());
            std::vector<Variable> output = std::vector<Variable>(size,Variable());

            std::vector<Variable> thisV = this->getVectorValue();
            std::vector<Variable> otherV = other.getVectorValue();

            for (unsigned long i = 0; i < size; i++)
            {
                if (i < thisV.size()) {
                    if (i < otherV.size())
                    output[i] = thisV[i] + otherV[i];
                } else if (i < thisV.size())
                        output[i] = thisV[i];
                else
                        output[i] = otherV[i];
            }

            return output;
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
