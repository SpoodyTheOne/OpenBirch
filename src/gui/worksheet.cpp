#include "worksheet.h"
#include "ui_worksheet.h"

Worksheet::Worksheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet)
{
    ui->setupUi(this);

    this->MainContentArea = ui->MainContentWindow;
}

Worksheet::~Worksheet()
{
    delete ui;
}
