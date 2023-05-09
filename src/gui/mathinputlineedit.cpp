#include "mathinputlineedit.h"

MathInputLineEdit::MathInputLineEdit(QWidget *parent)
 : QLineEdit(parent)
{
}

MathInputLineEdit::~MathInputLineEdit()
{
}

void MathInputLineEdit::focusInEvent(QFocusEvent* e)
{
    QLineEdit::focusInEvent(e);
    emit onFocused();
}
