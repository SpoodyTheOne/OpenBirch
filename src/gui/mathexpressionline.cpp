#include "mathexpressionline.h"
#include "matheditline.h"
#include "qevent.h"

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

void MathExpressionLine::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
        emit(changedLine(-1));
    else if (event->key() == Qt::Key_Down)
        emit(changedLine(1));
    else if (event->key() == Qt::Key_Backspace && this->cursorPosition() == 0) {
        if (this->text().isEmpty())
            std::cout << "deletus" << std::endl;
        else
            emit(changedLine(-1));
    }

    QLineEdit::keyPressEvent(event);
}
