#include "outputline.h"
#include "ui_outputline.h"

OutputLine::OutputLine(QWidget *parent) :
    WorksheetLine(parent),
    ui(new Ui::OutputLine)
{
    ui->setupUi(this);
}

OutputLine::~OutputLine()
{
    delete ui;
}
