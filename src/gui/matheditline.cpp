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
        throw std::runtime_error("Tried to evalute expression but there is not reference to the parent worksheet!");
    }

    // Evaluate expression
    this->evaluate();

    // If its the last math edit, then create a new one below
    if (this->worksheet->getIndexOfMathEdit(static_cast<MathEditFrame *>(this->parent())) == this->worksheet->getTotalMathEdits() - 1) {
        this->worksheet->createNewMathEditWidget();
    }

    // TODO Focus math edit below
}

void MathEditLine::evaluate()
{

}
