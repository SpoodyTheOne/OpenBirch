#include "testtextinput.h"
#include "ui_testtextinput.h"
#include "worksheet.h"

TestTextInput::TestTextInput(QWidget *parent) :
    MathLine(parent),
    ui(new Ui::TestTextInput)
{
    ui->setupUi(this);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &TestTextInput::evaluate);
}

TestTextInput::~TestTextInput()
{
    delete ui;
}

void TestTextInput::setParentWorksheet(Worksheet *parent)
{
    this->parent = parent;
}

QString TestTextInput::getText()
{
    return ui->lineEdit->text();
}

void TestTextInput::focus()
{
    ui->lineEdit->setFocus();
}

void TestTextInput::evaluate()
{
    parent->evaluateLine(this);
}

void TestTextInput::onEvaluated(MathOutput data)
{
    ui->label->setText(data.output);
}
