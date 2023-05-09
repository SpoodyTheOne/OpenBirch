#include "mathinputlineedit.h"
#include "qevent.h"

MathInputLineEdit::MathInputLineEdit(QWidget* parent)
 : QLineEdit(parent)
{}

MathInputLineEdit::~MathInputLineEdit()
{}

void MathInputLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit(focused());
}
