#include "errorline.h"
#include "ui_errorline.h"

ErrorLine::ErrorLine(Worksheet* parentWorksheet, QWidget *parent) :
    WorksheetLine(parentWorksheet, parent),
    ui(new Ui::ErrorLine)
{
    ui->setupUi(this);
}

ErrorLine::~ErrorLine()
{
    delete ui;
}

void ErrorLine::focus()
{}

QString ErrorLine::getText()
{
    return "";
}

void ErrorLine::setText(QString text)
{
    ui->label->setText(text);
}

LineType ErrorLine::getType()
{
    return LineType::Output;
}

void destroy();
void removeChildren();
