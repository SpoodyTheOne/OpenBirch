#include "outputline.h"
#include "ui_outputline.h"

OutputLine::OutputLine(Worksheet* parentWorksheet, QWidget *parent) :
    WorksheetLine(parentWorksheet, parent),
    ui(new Ui::OutputLine)
{
    ui->setupUi(this);

    ui->label->setFont(FontManager::MathFont());
}

OutputLine::~OutputLine()
{
    delete ui;
}

void OutputLine::focus()
{}

QString OutputLine::getText()
{
    return "";
}

LineType OutputLine::getType()
{
    return LineType::Output;
}
