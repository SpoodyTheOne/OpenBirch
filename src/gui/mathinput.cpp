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
    connect(ui->lineEdit, &MathInputLineEdit::onFocused, this, &MathInput::focus);
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
    std::cout << "foc" << std::endl;
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
    int offset = 0;

    if (data.error)
    {
        WorksheetLine* line = parentWorksheet->createLineRelative(LineType::Error,this,++offset,false);
        line->setText(data.error_msg);
    } else if (!QString(data.output).isEmpty()) {
        WorksheetLine* line = parentWorksheet->createLineRelative(LineType::Output,this,++offset,false);
        line->setText(data.output);
    }

    if (parentWorksheet->isAtEnd(1))
        parentWorksheet->createLineRelative(LineType::Math, nullptr, ++offset, true);
}
