#include "matheditoutput.h"
#include "ui_matheditoutput.h"

MathEditOutput::MathEditOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditOutput)
{
    ui->setupUi(this);
}

MathEditOutput::~MathEditOutput()
{
    delete ui;
}
