#include "matheditwidget.h"
#include "ui_matheditwidget.h"
#include "worksheet.h"
#include <iostream>

MathEditWidget::MathEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditWidget)
{
    ui->setupUi(this);
    std::cout << "Creating math edit..." << std::endl;
}

MathEditWidget::~MathEditWidget()
{
    std::cout << "Destroying math edit widget..." << std::endl;
    delete ui;
}

void MathEditWidget::on_expressionLine_returnPressed()
{
    if (this->worksheet == nullptr) {
        throw std::runtime_error("Tried to evalute expression but there is not reference to the parent worksheet!");
    }

    // Evaluate expression
    this->evaluate();

    // If its the last math edit, then create a new one below
    if (this->worksheet->getIndexOfMathEdit(this) == this->worksheet->getTotalMathEdits() - 1) {
        this->worksheet->createNewMathEditWidget();
    }

    // TODO Focus math edit below
}

void MathEditWidget::evaluate()
{

}
