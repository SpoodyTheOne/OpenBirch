#include "expressiontreevisualizer.h"
#include "ui_expressiontreevisualizer.h"

#include <QPainter>
#include <QImage>
#include <iostream>

ExpressionTreeVisualizer::ExpressionTreeVisualizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpressionTreeVisualizer)
{
    ui->setupUi(this);
    this->setWindowTitle(ExpressionTreeVisualizer::windowTitle);
}

ExpressionTreeVisualizer::~ExpressionTreeVisualizer()
{
    delete ui;
}

void ExpressionTreeVisualizer::visualizeExpressionTree(Node* root)
{
    std::cout << "Drawing tree..." << std::endl;
//    painter.drawEllipse(QPoint( 300, 300 ), 50, 50);

}
