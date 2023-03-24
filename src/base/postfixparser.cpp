#include "postfixparser.h"

#include "base/operators/operator.h"
#include "base/operators/parenthesis.h"
#include "base/operators/multiply.h"
#include "base/operators/operatorfactory.h"
#include "base/operators/subtraction.h"
#include "base/operators/negate.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <QString>

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

    bool prevWasOperand = false;

    for (size_t i = 0; i < expressionLen; i++)
    {
        std::string tokenSequence = PostFixParser::getSequence(QString(expression.c_str()), i, expressionLen - i);

//        std::cout << "seq: " << tokenSequence << std::endl;
        i += tokenSequence.size() - 1;
        try
        {
            auto value = PreciseValue(tokenSequence);
            result.append(tokenSequence);
            result += ' ';
            prevWasOperand = true;
            continue;
        }
        catch (const std::exception& e)
        {} // TODO handle overflow/underflow errors, see doc

        // The token sequence is not a operand
        Operator* op = OperatorFactory::create(tokenSequence);

        // If the token seq isn't an operator treat it as an operand
        if (op == nullptr) {
            // not a number, assume variable
            if(tokenSequence.find_first_not_of(' ') == std::string::npos)
                continue;

            result.append(tokenSequence);
            result += ' ';
            prevWasOperand = true;
            continue;
        }

        std::cout << op->getName() << std::endl;

        // The token is an operator

        if (operatorStack.empty() || op->getSign() == LParenthesis::sign)
        {
            if (!prevWasOperand)
                if (op->getSign() == Subtraction::sign)
                    op = OperatorFactory::create(Negate::sign);

            operatorStack.push(op);
            prevWasOperand = false;
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
            prevWasOperand = false;
            continue;
        }

        if (!prevWasOperand)
            if (op->getSign() == Subtraction::sign)
                op = OperatorFactory::create(Negate::sign);

        while (!operatorStack.empty())
        {
            if (op->getPredecence() > operatorStack.top()->getPredecence())
                break;

            if (operatorStack.top()->getSign() == LParenthesis::sign)
                break;

            if (operatorStack.top()->getSign() == Negate::sign && op->getSign() == Negate::sign)
                break;

            if (op->getPredecence() == operatorStack.top()->getPredecence())
                if (operatorStack.top()->getAssociativity() == OperatorAssociativity::Right)
                    break;

            result.append(operatorStack.top()->getSign());
            result += ' ';
            operatorStack.pop();
            prevWasOperand = false;
        }

        prevWasOperand = false;
        operatorStack.push(op);
    }

    while(!operatorStack.empty())
    {
        result.append(operatorStack.top()->getSign());
        result += ' ';
        operatorStack.pop();
    }

    std::cout << "result: " << result << std::endl;
    return result;
}

std::string PostFixParser::getSequence(QString input, int startIdx, int lengthLeft)
{
    // TODO validate input

    // Whether the sequence consists of symbol(s) or number(s)
    bool checkForNum = isdigit(input.toStdString()[startIdx]);
    QString sequence;
    sequence += input[startIdx];

    // The latest operator found
    QString lastFoundOperator;

    if (lengthLeft == 1)
        return sequence.toStdString();

    if (checkForNum)
    {
        for (int i = startIdx + 1; i < startIdx + lengthLeft; i++) {
            if (isdigit(input.toStdString()[i]) || input.toStdString()[i] == '.') { // TODO delimeter settings, so it can be ','
                sequence += input[i];
            }
            else
                break;
        }
    }
    else
    {
        for (int i = startIdx + 1; i < startIdx + lengthLeft; i++) {

            if (OperatorFactory::IsOperator(sequence.toStdString()))
                lastFoundOperator = sequence;

            if (isalpha(input.toStdString()[i]))
                sequence += input[i];
            else
                break;
        }
    }

    if (!lastFoundOperator.isEmpty())
        return lastFoundOperator.toStdString();

    std::cout << sequence.toStdString() << std::endl;

    return sequence.toStdString();
}
