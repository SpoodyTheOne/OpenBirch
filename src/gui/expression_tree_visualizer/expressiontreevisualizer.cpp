#include "expressiontreevisualizer.h"
#include "ui_expressiontreevisualizer.h"

#include <QPainter>
#include <QImage>
#include <QGraphicsTextItem>
#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>
#include <stack>

ExpressionTreeVisualizer::ExpressionTreeVisualizer(Node* treeRoot, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpressionTreeVisualizer)
{
    ui->setupUi(this);

    this->treeRoot = treeRoot;
    this->graphicsScene = new QGraphicsScene;
    this->mainView = ui->expressionTreeGraphicsView;
    this->mainView->setScene(this->graphicsScene);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle(ExpressionTreeVisualizer::windowTitle);
}

ExpressionTreeVisualizer::~ExpressionTreeVisualizer()
{
    std::cout << "Destroying visulizaer " << std::endl;
    delete treeRoot;
    delete ui;
}

void ExpressionTreeVisualizer::visualizeExpressionTree()
{
    Node* root = this->treeRoot;
    if (!root)
        return;

    treeRoot = root;

    std::queue<Node *> siblingsInLevel;
    int height = getHeight(root);
    std::cout << "height: " << height << std::endl;

    siblingsInLevel.push(root);
    int currentLevel{0};
    bool leftSide{false};
    do {
        int siblingCount = siblingsInLevel.size(); // Count of siblings on this level

        // y-coordinate is propoprtional with the level we're currently drawing
        float levelYCord = ExpressionTreeVisualizer::levelDrawDist * currentLevel;

        // Draw all nodes in this level and add all children of next level to queue
        while (siblingCount--)
        {
            // The new root node of the new sub tree
            Node* subRoot = siblingsInLevel.front();
            siblingsInLevel.pop();

            float xPos = subRoot->parent->absolutePosition;
            if (currentLevel > 0)
            {
                if (leftSide)
                    xPos -= ExpressionTreeVisualizer::levelDrawSpread * (height - currentLevel);
                else
                    xPos += ExpressionTreeVisualizer::levelDrawSpread * (height - currentLevel);

            }

            printNode(subRoot->getInformation(), xPos, levelYCord);
            std::cout << "Printing node: " << subRoot->getInformation().toStdString() << " at x: " << std::to_string(xPos) << std::endl;

            for (size_t i = 0; i < subRoot->children.size(); i++)
            {
                siblingsInLevel.push(subRoot->children[i]);
            }

            subRoot->absolutePosition = xPos;
            leftSide = !leftSide;
        }
        currentLevel++;
    } while (!siblingsInLevel.empty());
}

void ExpressionTreeVisualizer::printNode(QString content, float x, float y)
{

    this->graphicsScene->addEllipse(x, y, 50, 50);
    QGraphicsTextItem *text = this->graphicsScene->addText(content);
    text->setPos(x, y);
}

int ExpressionTreeVisualizer::getHeight(Node* root)
{
    if (!root)
        return -1;

    std::queue<Node *> siblings;
    siblings.push(root);
    int height{0};

    do
    {
        Node* subRoot = siblings.front();

        size_t siblingsInLevel = siblings.size();

        while (siblingsInLevel--)
        {
            siblings.pop();
            for (size_t i = 0; i < subRoot->children.size(); i++)
            {
                siblings.push(subRoot->children[i]);
            }
        }
        height++;
    } while (!siblings.empty());
    return height;
}









