#ifndef MATHEXPRESSIONLINE_H
#define MATHEXPRESSIONLINE_H

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class MathExpressionLine : public QLineEdit
{
  Q_OBJECT

public:
  MathExpressionLine(QWidget *parent = 0);
  ~MathExpressionLine();

signals:
  void focussed(bool hasFocus);

protected:
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);
};
#endif // MATHEXPRESSIONLINE_H
