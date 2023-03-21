#include "parser.h"
#include "base/deprecated/expression_parser/operatornode.h"
#include "base/deprecated/expression_parser/symboltable.h"
#include "base/deprecated/expression_parser/variablenode.h"
#include "constantnode.h"
#include "base/deprecated/expression_parser/postfix_parser/postfixparser.h"
#include "base/deprecated/operators/operator.h"
#include "base/deprecated/operators/operatorfactory.h"
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

QString Parser::evaluate(SymbolTable *symbolTable, bool keepTree)
{
    if (this->treeRoot == nullptr)
        return "";

    ExpressionValue out = this->treeRoot->evaluate(symbolTable);

    if (outputMode == ParserOutputMode::Variable)
    {        
        std::cout << outputSymbol << ": " << out << std::endl;
        SymbolDefinition newSymbol = SymbolDefinition(out);
        symbolTable->defineSymbol(outputSymbol,newSymbol);

        return QString( (outputSymbol + " = " + out.get_str()).c_str() );
    } else if (outputMode == ParserOutputMode::Compare)
        return out.isValid() ? "True" : "False";

    if (!keepTree)
        delete this->treeRoot;

    return QString(out.get_str().c_str());
}

QString Parser::compile(SymbolTable *symbolTable) {
    //this is where the fun begins :)

    QRegExp re_equals(" *(=) *");
    QRegExp re_define(" *:= *");
    QString expression = QString(m_Expression.c_str());

    if (expression.contains(re_define))
    {
        QStringList parts = expression.split(re_define);

        if (parts.length() > 2) // more than 1 equals sign
            return "Can't have multiple define (:=) symbols in an expression";

        expression = parts.last();

        outputMode = ParserOutputMode::Variable;
        outputSymbol = parts.first().toStdString();
    }

    if (expression.contains(re_equals))
        outputMode = ParserOutputMode::Compare;

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

        std::string tokenSequence = PostFixParser::getSequence(QString(postfix.c_str()), i, postfixLen - i);
        i += tokenSequence.size() - 1;
        ExpressionValue operand;

        std::cout << "seq: " << tokenSequence << std::endl;

        // TODO check for variable in symboltable

        try
        {
            // The token sequence is an operand, so just push a leaf node to the stack
            operand = ExpressionValue(tokenSequence);
            Node* leafNode = new ConstantNode(operand);
            treeStack.push(leafNode);
            continue;
        }
        catch (const std::exception& e) { } // TODO handle overflow/underflow errors, see doc

        Operator* op = OperatorFactory::create(tokenSequence);
        if (op == nullptr) {

            SymbolDefinition *var = symbolTable->getSymbol(tokenSequence);

            if (!var) {
                //errorCompile("Unknown keyword, operator or variable: " + tokenSequence);
                //break;
            }

            // The token sequence is a variable, so just push a leaf node to the stack
            Node* leafNode = new VariableNode(tokenSequence);
            treeStack.push(leafNode);
            continue;
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

    if (err_msg.empty() && postfixLen > 0)
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

