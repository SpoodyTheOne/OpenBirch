#include "lexer.h"

namespace BirchLang {

Lexer::Lexer(std::string input)
{
    this->source = input;
    this->tokenize();
}

void Lexer::tokenize()
{

}

}
