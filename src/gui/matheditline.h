#ifndef MATHEDITLINE_H
#define MATHEDITLINE_H

#include "base/deprecated/expression_parser/parser.h"
#include "worksheetline.h"
#include "mathexpressionline.h"
#include <QWidget>
#include <QKeyEvent>

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
protected:
    void onFocus(bool focussed);
    void onChangeLine(int);
    void removeLine();
    void returnPressed(QKeyEvent*);

private:
    Ui::MathEditLine *ui;
    WorksheetLine* parentFrame{};
    Node* treeRoot{};
    bool unevaluatedChanges{true};

    void evaluate(bool showInline = false, bool keepTree = false);
    void onExpressionChanged(const QString& text);
    Worksheet* getWorksheet() const;
};

#endif // MATHEDITLINE_H
