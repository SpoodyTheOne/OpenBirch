#include "mathinput.h"
#include "ui_mathinput.h"
#include "mathinputlineedit.h"


MathInput::MathInput(Worksheet* worksheet, QWidget *parent) :
    MathLine(worksheet, parent),
    ui(new Ui::MathInput)
{
    ui->setupUi(this);

    ui->lineEdit->setFont(FontManager::MathFont());

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MathInput::evaluate);
    //connect(ui->lineEdit, &MathInputLineEdit::focused, this, &MathInput::focus);
}

MathInput::~MathInput()
{
    delete ui;
}

QString MathInput::getText()
{
    return ui->lineEdit->text();
}

void MathInput::setText(QString text)
{
    ui->lineEdit->setText(text);
}

void MathInput::focus()
{
    ui->lineEdit->setFocus();
    parentWorksheet->setFocusedLine(this);
}

void MathInput::evaluate()
{
    removeChildren();
    parentWorksheet->evaluateLine(this);
}

void MathInput::onEvaluated(MathOutput data)
{
    if (parentWorksheet->isAtEnd())
        parentWorksheet->createLineRelative(LineType::Math, nullptr, 1, true);

    WorksheetLine* line = parentWorksheet->createLineRelative(LineType::Output,this,1,false);
    line->setText(data.error ? data.error_msg : data.output);
}
