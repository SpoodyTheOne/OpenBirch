#include "expressiontreevisualizer.h"
#include "ui_expressiontreevisualizer.h"

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

}
