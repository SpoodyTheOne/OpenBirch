#ifndef EXPRESSIONTREEVISUALIZER_H
#define EXPRESSIONTREEVISUALIZER_H

#include <QWidget>
#include "base/expression_parser/node.h"

namespace Ui {
class ExpressionTreeVisualizer;
}

class ExpressionTreeVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit ExpressionTreeVisualizer(QWidget *parent = nullptr);
    ~ExpressionTreeVisualizer();

    static void visualizeExpressionTree(Node* root);
private:
    Ui::ExpressionTreeVisualizer *ui;
    const QString windowTitle{"Expression Tree Visualizer"};
};

#endif // EXPRESSIONTREEVISUALIZER_H
