#include "testtextinput.h"
#include "ui_testtextinput.h"
#include "worksheet.h"
#include <iostream>

TestTextInput::TestTextInput(Worksheet* worksheet, QWidget *parent) :
    MathLine(parent),
    ui(new Ui::TestTextInput),
    parentWorksheet(worksheet)
{
    ui->setupUi(this);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &TestTextInput::evaluate);
}

TestTextInput::~TestTextInput()
{
    delete ui;
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
    parentWorksheet->evaluateLine(this);
}

void TestTextInput::onEvaluated(MathOutput data)
{
    if (data.error)
        ui->label->setText(data.error_msg);
    else
        ui->label->setText(data.output);
}
