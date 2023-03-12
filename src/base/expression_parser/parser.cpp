#include "parser.h"
#include "base/expression_parser/operatornode.h"
#include "constantnode.h"
#include "base/expression_parser/postfix_parser/postfixparser.h"
#include "base/operators/operator.h"
#include "base/operators/operatorfactory.h"

#include <QString>
#include <stack>

Parser::Parser(QString input)
{
    m_Expression = input.toStdString();
}

Parser::~Parser()
{

}


Parser::Parser(std::string input)
{
    m_Expression = input;
}

bool isNumber(char c);

void Parser::compile() {
    //this is where the fun begins :)

    std::string postfix = PostFixParser::parseExpression(m_Expression);

    std::cout << "postfix: " << postfix << std::endl;

    std::stack<Node *> treeStack;
    size_t postfixLen = postfix.size();
    for (size_t i = 0; i < postfixLen; i++)
    {
        if (postfix[i] == ' ')
            continue;

        std::string tokenSequence = PostFixParser::getSequence(postfix, i, postfixLen - i);
        i += tokenSequence.size() - 1;
        Number operand;

        std::cout << "seq: " << tokenSequence << std::endl;

        // TODO check for variable in symboltable

        try
        {
            // The token sequence is an operand, so just push a leaf node to the stack
            operand = std::stod(tokenSequence);
            Node* leafNode = new ConstantNode(operand);
            treeStack.push(leafNode);
            continue;
        }
        catch (const std::exception& e) { } // TODO handle overflow/underflow errors, see doc

        Operator* op = OperatorFactory::create(tokenSequence);
        if (op == nullptr) {
            throw std::invalid_argument("Unkown keyword/operator or variable: " + tokenSequence);
        }

        // TODO support for unary operator (only pop one operand from stack)
        if (treeStack.size() < 2) {
            throw std::runtime_error("Operator: " + op->getSign() + " found, but there are no operands");
        }

        Node* opNode = new OperatorNode(op);

        opNode->rightChild = treeStack.top();
        treeStack.pop();

        opNode->leftChild = treeStack.top();
        treeStack.pop();

        treeStack.push(opNode);
    }
    this->treeRoot = treeStack.top();
}

bool isNumber(char c) {
    return (c <= 57) && (c >= 48);
}
