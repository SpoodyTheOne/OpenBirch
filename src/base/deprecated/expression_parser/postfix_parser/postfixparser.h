#ifndef POSTFIXPARSER_H
#define POSTFIXPARSER_H

#include <iostream>
#include <QString>

class PostFixParser
{
public:
    PostFixParser();

    /**
     * @brief converts a infix algebraic expression to a postfix (RPN) expression.
     * @param expression: the expression to convert to postfix expression.
     * @return the postfix expression.
     */
    static std::string parseExpression(std::string expression);

    /**
     * @brief gets a sequence of either chars or numbers. Will get all consecutive numbers or chars until another type is found.
     * @param input
     * @param startIdx
     * @param lengthLeft
     * @return a string with the sequence.
     */
    static std::string getSequence(QString input, int startIdx, int lengthLeft);
};

#endif // POSTFIXPARSER_H
