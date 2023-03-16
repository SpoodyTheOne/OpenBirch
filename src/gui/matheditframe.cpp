#include "matheditframe.h"
#include "ui_matheditframe.h"
#include "matheditline.h"
#include "worksheet.h"
#include <iostream>

MathEditFrame::MathEditFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditFrame)
{
    ui->setupUi(this);
    this->mainFrame = this->findChild<QFrame *>("frame");
//    this->setFocusPolicy(Qt::StrongFocus);
}

MathEditFrame::~MathEditFrame()
{
    std::cout << "Detroyed mth vframe" << std::endl;

    delete ui;
}

QFrame* MathEditFrame::getMainFrame() const
{
    return this->mainFrame;
}

Worksheet* MathEditFrame::getWorksheet() const
{
    return this->worksheet;
}

MathEditLine* MathEditFrame::getMathEditLine() const
{
    return this->mainFrame->findChild<MathEditLine *>("MathEditLine");
}

void MathEditFrame::mousePressEvent(QMouseEvent *event)
{
    this->worksheet->setFocusedMathFrame(this);
    event->accept();
}

//void MathEditFrame::focusInEvent(QFocusEvent* e)
//{
//    std::cout << "fouces" << std::endl;
//    this->getWorksheet()->setFocusedMathFrame(this);
//}
