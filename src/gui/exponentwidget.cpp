#include "exponentwidget.h"
#include "ui_exponentwidget.h"

ExponentWidget::ExponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExponentWidget)
{
    ui->setupUi(this);
}

ExponentWidget::~ExponentWidget()
{
    delete ui;
}
