#ifndef MATHEDITLINE_H
#define MATHEDITLINE_H

#include "matheditframe.h"
#include "mathexpressionline.h"
#include <QWidget>

namespace Ui {
class MathEditLine;
}

class Worksheet;

class MathEditLine : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditLine(QWidget *parent = nullptr);
    ~MathEditLine();

    /**
     * @brief gets the QLineEdit object on this math edit line. The actual line edit object where expression is edited
     * @return the QLineEdit object on this math edit line.
     */
    MathExpressionLine* getExpressionLine();

    friend Worksheet;
private slots:
    void on_expressionLine_returnPressed();
protected:
    void onFocus(bool focussed);

private:
    Ui::MathEditLine *ui;
    MathEditFrame* parentFrame;

    void evaluate();
    Worksheet* getWorksheet() const;
};

#endif // MATHEDITLINE_H
