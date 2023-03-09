#include "worksheet.h"
#include "matheditwidget.h"
#include "ui_worksheet.h"
#include <iostream>

Worksheet::Worksheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet)
{
    ui->setupUi(this);

    this->mainContentArea = ui->MainContentWindow;

    // Create start edit field, when its a new empty worksheet
    this->createNewMathEditWidget();
}

Worksheet::~Worksheet()
{
    delete ui;
}

QVBoxLayout* Worksheet::getMainContentArea() const
{
    return mainContentArea;
}

MathEditWidget* Worksheet::createNewMathEditWidget()
{
    QVBoxLayout* parent = this->mainContentArea;
    int idx = this->lines.size();
    if (parent == nullptr) {
        throw std::runtime_error("No parent layout while creating new math edit widget.");
    }

    if (idx < 0)
    {
        throw std::runtime_error("Index was negative while creating new math edit widget.");
    }

    MathEditWidget* mathEditWidget = new MathEditWidget;

    // Make sure the math edit knows what worksheets its in
    mathEditWidget->worksheet = this;

    // Store reference in worksheets record of lines
    this->lines.push_back(mathEditWidget);

    parent->insertWidget(idx, mathEditWidget);
    return mathEditWidget;
}

int Worksheet::getTotalMathEdits()
{
    return this->lines.size();
}

int Worksheet::getIndexOfMathEdit(MathEditWidget* mathEdit)
{
    if (this->mainContentArea == nullptr) {
        throw std::runtime_error("No parent layout where mathedits are inserted into.");
    }

    int idx = this->mainContentArea->indexOf(mathEdit);
    if (idx < 0) {
        throw std::runtime_error("Math edit not found in layout. This might be because the math edit is not part of this worksheet.");
    }
    return idx;
}
