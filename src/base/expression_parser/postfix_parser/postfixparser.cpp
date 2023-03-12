#include "postfixparser.h"

#include "base/operators/operator.h"
#include "base/operators/parenthesis.h"
#include "base/operators/operatorfactory.h"
#include <iostream>
#include <stack>

PostFixParser::PostFixParser()
{

}

std::string PostFixParser::parseExpression(std::string expression)
{
    if (expression.empty())
        return std::string();

    std::string result;
    std::stack<Operator *> operatorStack;
    size_t expressionLen = expression.size();

    for (size_t i = 0; i < expressionLen; i++)
    {
        std::string tokenSequence = PostFixParser::getSequence(expression, i, expressionLen - i);
        std::cout << "seq: " << tokenSequence << std::endl;
        i += tokenSequence.size() - 1;
        try
        {
            std::stod(tokenSequence); // TODO maybe use Number functionallity for string conversion?
            result.append(tokenSequence);
            result += ' ';
            continue;
        }
        catch (const std::exception& e) { } // TODO handle overflow/underflow errors, see doc

        // The token sequence is not a operand
        Operator* op = OperatorFactory::create(tokenSequence);

        // If the token seq isn't a operator treat it as a operand
        if (op == nullptr) {
            result.append(tokenSequence);
            result += ' ';
            continue;
        }

        std::cout << op->getName() << std::endl;

        // The token is a operator

        if (operatorStack.empty() || op->getSign() == LParenthesis::sign)
        {
            operatorStack.push(op);
            continue;
        }

        if (op->getSign() == RParenthesis::sign)
        {
            while (!operatorStack.empty())
            {
                // Corresponding left bracket is found
                if (operatorStack.top()->getSign() == LParenthesis::sign)
                {
                    operatorStack.pop();
                    break;
                }

                result.append(operatorStack.top()->getSign());
                result += ' ';
                operatorStack.pop();
            }
            continue;
        }

        while (!operatorStack.empty())
        {
            if (op->getPredecence() > operatorStack.top()->getPredecence())
                break;

            if (operatorStack.top()->getSign() == LParenthesis::sign)
                break;

            result.append(operatorStack.top()->getSign());
            result += ' ';
            operatorStack.pop();
        }
        operatorStack.push(op);

        // TODO somewhere check for variables in symboltable

    }

    while(!operatorStack.empty())
    {
        result.append(operatorStack.top()->getSign());
        result += ' ';
        operatorStack.pop();
    }

    // Strip last whitespace
    if (result[result.size() - 1] == ' ')
        result.pop_back();

    std::cout << "result: " << result << std::endl;
    return result;
}

std::string PostFixParser::getSequence(std::string& input, size_t startIdx, size_t lengthLeft)
{
    // TODO validate input

    // Whether the sequence consists of symbol(s) or number(s)
    bool checkForNum = isdigit(input[startIdx]);
    std::string sequence;
    sequence += input[startIdx];

    if (lengthLeft == 1)
        return sequence;

    if (checkForNum)
    {
        for (size_t i = startIdx + 1; i < startIdx + lengthLeft; i++) {
            if (isdigit(input[i]) || input[i] == '.') { // TODO delimeter settings, so it can be ','
                sequence += input[i];
            }
            else
                break;
        }
    }
    else
    {
        for (size_t i = startIdx + 1; i < startIdx + lengthLeft; i++) {
            if (isalpha(input[i])) {
                sequence += input[i];
            }
            else
                break;
        }
    }

    return sequence;
}
