#include "expressions.h"

void Expressions::initialize() {
    Expressions::parser = new parser_t();
    Expressions::symbol_table = new symbol_table_t();
}
