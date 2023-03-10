#include "matheditline.h"
#include "ui_matheditline.h"
#include "worksheet.h"
#include <iostream>

MathEditLine::MathEditLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditLine)
{
    ui->setupUi(this);
    std::cout << "Creating math edit..." << std::endl;
}

MathEditLine::~MathEditLine()
{
    std::cout << "Destroying math edit widget..." << std::endl;
    delete ui;
}

void MathEditLine::on_expressionLine_returnPressed()
{
    if (this->worksheet == nullptr) {
        throw std::runtime_error("Tried to evalute expression but there is no reference to the parent worksheet!");
    }

    if (this->parentFrame == nullptr) {
        throw std::runtime_error("Tried to evaluate expression, but there is no reference to the math frame of this math line!");
    }

    // Evaluate expression
    this->evaluate();

    // If its the last math edit, then create a new one below
    if (this->worksheet->getIndexOfMathFrame(this->parentFrame) == this->worksheet->getTotalMathEdits() - 1) {
        MathEditFrame* mathFrame = this->worksheet->createNewMathEditWidget();
        mathFrame->getMathEditLine()->getExpressionLine()->setFocus();
    }
    else
    {
        // Focus math edit below
        QWidget::focusNextChild();
    }
}

QLineEdit* MathEditLine::getExpressionLine() {
    return this->findChild<QLineEdit *>("expressionLine");
}

void MathEditLine::evaluate()
{

}
