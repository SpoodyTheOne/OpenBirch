#include "parser.h"
#include "base/expression_parser/constantnode.h"

#include <QString>

Parser::Parser(QString input)
{
    m_Expression = input.toStdString();
    m_expressionTree = new Tree();
}

Parser::~Parser()
{
    delete m_expressionTree;
}


Parser::Parser(std::string input)
{
    m_Expression = input;
}

bool isNumber(char c);

void Parser::compile() {
    //this is where the fun begins :)

    state = ParserState::Working;

    std::string WordReg     = "";
    std::string OperandReg  = "";
    int expression_end  = false;
    Node *currentWorkingNode = new Node();

    const char *expression = m_Expression.c_str();
    size_t i = 0;

    while (!expression_end) {
        char c = expression[0];

        // last character
        if (i >= strlen(expression)) {
            if (!isNumber(c) && c != ')') { // Unclosed parenthesis
                expression_end = 1;
                errorCompile("Unclosed Parenthesis");
            } else {
                WordReg = WordReg + c;
                Number value = Number(std::stod(WordReg));
                ConstantNode *node = new ConstantNode(value);
                currentWorkingNode->setChild(node,true);
            }

        }

        if (isNumber(c)) {
            if (!OperandReg.empty()) {
                expression_end = 1;
                errorCompile("Unclosed Parenthesis");
            }
        }
    }
}

bool isNumber(char c) {
    return (c <= 57) && (c >= 48);
}
