#include "worksheetline.h"
#include "ui_worksheetline.h"

WorksheetLine::WorksheetLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorksheetLine)
{
    ui->setupUi(this);
}

WorksheetLine::~WorksheetLine()
{
    delete ui;
}
