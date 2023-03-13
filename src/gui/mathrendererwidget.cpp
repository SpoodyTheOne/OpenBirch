#include "mathrendererwidget.h"
#include "ui_mathrendererwidget.h"

MathRendererWidget::MathRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathRendererWidget)
{
    ui->setupUi(this);
}

MathRendererWidget::~MathRendererWidget()
{
    delete ui;
}
