#include "matheditframe.h"
#include "ui_matheditframe.h"
#include "matheditline.h"

MathEditFrame::MathEditFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditFrame)
{
    ui->setupUi(this);
    this->mainFrame = this->findChild<QFrame *>("frame");
}

MathEditFrame::~MathEditFrame()
{
    delete ui;
}

QFrame* MathEditFrame::getMainFrame() const {
    return mainFrame;
}

MathEditLine* MathEditFrame::getMathEditLine() const {
    return this->mainFrame->findChild<MathEditLine *>("MathEditLine");
}
