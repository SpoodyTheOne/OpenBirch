#include "matheditframe.h"
#include "ui_matheditframe.h"

MathEditFrame::MathEditFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditFrame)
{
    ui->setupUi(this);
}

MathEditFrame::~MathEditFrame()
{
    delete ui;
}

QFrame* MathEditFrame::getMainFrame() {
    return this->findChild<QFrame *>("frame");
}
