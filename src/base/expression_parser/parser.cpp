#include "parser.h"

#include <QString>

Parser::Parser(QString input)
{
    m_Expression = input.toStdString();
}

Parser::Parser(std::string input)
{
    m_Expression = input;
}

Parser::~Parser()
{

}

