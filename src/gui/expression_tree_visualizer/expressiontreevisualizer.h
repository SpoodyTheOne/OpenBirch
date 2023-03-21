#ifndef EXPRESSIONTREEVISUALIZER_H
#define EXPRESSIONTREEVISUALIZER_H

#include <QWidget>
#include <QGraphicsView>
#include "base/deprecated/expression_parser/node.h"

namespace Ui {
class ExpressionTreeVisualizer;
}

class ExpressionTreeVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit ExpressionTreeVisualizer(Node* treeRoot, QWidget *parent = nullptr);
    ~ExpressionTreeVisualizer();

    /**
     * @brief displays a binary tree in a pretty way
     * @param root: the root node of the binary tree to display
     * @details uses a reverse leveled traversion of the binary tree,
     * to get every sibling at every level starting from the bottom.
     * With that we can calculate the position where each node should be.
     */
    void visualizeExpressionTree();
private:
    Ui::ExpressionTreeVisualizer *ui;
    const QString windowTitle{"Expression Tree Visualizer"};
    const float levelDrawDist{100};
    const float levelDrawSpread{75};
    const float nodeDrawRadius{50};
    QGraphicsScene* graphicsScene{};
    QGraphicsView* mainView{};

    void printNode(QString content, float x, float y);
    int getHeight(Node* root);

    Node* treeRoot{};
};

#endif // EXPRESSIONTREEVISUALIZER_H
