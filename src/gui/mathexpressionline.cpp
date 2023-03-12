#include "mathexpressionline.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <iostream>

MathExpressionLine::MathExpressionLine(QWidget *parent)
 : QLineEdit(parent)
{}

MathExpressionLine::~MathExpressionLine()
{}

void MathExpressionLine::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  emit(focussed(true));
}

void MathExpressionLine::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  emit(focussed(false));
}
