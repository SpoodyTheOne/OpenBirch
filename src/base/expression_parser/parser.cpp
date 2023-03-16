#include "parser.h"
#include "base/expression_parser/operatornode.h"
#include "constantnode.h"
#include "base/expression_parser/postfix_parser/postfixparser.h"
#include "base/operators/operator.h"
#include "base/operators/operatorfactory.h"
#include "qregexp.h"

#include <QString>
#include <QStringList>
#include <stack>

Parser::Parser(QString input)
{
    m_Expression = input.toStdString();
}

Parser::~Parser()
{}

Parser::Parser()
{

}


Parser::Parser(std::string input)
{
    m_Expression = input;
}

QString Parser::evaluate()
{
    if (this->treeRoot == nullptr)
        return "";

    ExpressionValue out = this->treeRoot->evaluate();

    //if (outputMode == ParserOutputMode::Variable)
        // Define symbol in symbol table here

    return QString(out.print().c_str());
}

QString Parser::compile() {
    //this is where the fun begins :)

    QRegExp re_equals("(=|:=)");
    QString expression = QString(m_Expression.c_str());

    if (expression.contains(re_equals))
    {
        QStringList parts = expression.split(re_equals);

        if (parts.length() > 2) // more than 1 equals sign
            return "Support for more than 1 equals sign not implemented yet";

        expression = parts.last();

        outputMode = ParserOutputMode::Variable;
        outputSymbol = parts.first().toStdString();
    }

    std::string postfix = PostFixParser::parseExpression(expression.toStdString());

    err_msg = "";
    state = ParserState::Working;

    std::cout << "postfix: " << postfix << std::endl;

    std::stack<Node *> treeStack;
    size_t postfixLen = postfix.size();

    std::cout << postfixLen << std::endl;

    for (size_t i = 0; i < postfixLen; i++)
    {
        if (postfix[i] == ' ')
            continue;

        std::string tokenSequence = PostFixParser::getSequence(postfix, i, postfixLen - i);
        i += tokenSequence.size() - 1;
        ExpressionValue operand;

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
            errorCompile("Unkown keyword, operator or variable: " + tokenSequence);
            break;
        }

        // TODO support for unary operator (only pop one operand from stack)
        if (treeStack.size() < op->getArgumentCount()) {
            errorCompile("Operator: '" + op->getSign() + "' found, but there are no operands");
            break;
        }

        Node* opNode = new OperatorNode(op);

        for (int i = 0; i < op->getArgumentCount(); i++) {
            // Insert child nodes so left is first index
            opNode->children.insert(opNode->children.begin(), treeStack.top());
            treeStack.top()->parent = opNode;
            treeStack.pop();
        }

        treeStack.push(opNode);
    }

    if (postfixLen > 0)
        this->treeRoot = treeStack.top();

    return QString(err_msg.c_str());
}

void Parser::setExpression(QString expression)
{
    this->m_Expression = expression.toStdString();
}

Node* Parser::getTreeRoot() const
{
    return this->treeRoot;
}

