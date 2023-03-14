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

  void keyPressEvent(QKeyEvent *event);

signals:
  void focussed(bool hasFocus);
  void changedLine(int amount);

protected:
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);
};
#endif // MATHEXPRESSIONLINE_H
