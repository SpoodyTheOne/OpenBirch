#include "outputline.h"
#include "ui_outputline.h"

OutputLine::OutputLine(Worksheet* parentWorksheet, QWidget *parent) :
    WorksheetLine(parentWorksheet, parent),
    ui(new Ui::OutputLine)
{
    ui->setupUi(this);
}

OutputLine::~OutputLine()
{
    delete ui;
}
