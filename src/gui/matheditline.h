#ifndef MATHEDITLINE_H
#define MATHEDITLINE_H

#include "base/expression_parser/parser.h"
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
    Node* getTreeRoot() const;
    friend Worksheet;
private slots:
    void on_expressionLine_returnPressed();
protected:
    void onFocus(bool focussed);
    void onChangeLine(int);

private:
    Ui::MathEditLine *ui;
    MathEditFrame* parentFrame{};
    Node* treeRoot{};
    bool unevaluatedChanges{true};

    void evaluate();
    void onExpressionChanged(const QString& text);
    Worksheet* getWorksheet() const;
};

#endif // MATHEDITLINE_H
