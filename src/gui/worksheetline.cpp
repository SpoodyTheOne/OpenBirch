#include "worksheetline.h"
#include "ui_matheditframe.h"
#include "matheditline.h"
#include "worksheet.h"
#include <iostream>

WorksheetLine::WorksheetLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorksheetLine)
{
    ui->setupUi(this);
    this->mainFrame = this->findChild<QFrame *>("frame");
//    this->setFocusPolicy(Qt::StrongFocus);
}

WorksheetLine::~WorksheetLine()
{
    std::cout << "Detroyed mth vframe" << std::endl;

    delete ui;
}

QFrame* WorksheetLine::getMainFrame() const
{
    return this->mainFrame;
}

Worksheet* WorksheetLine::getWorksheet() const
{
    return this->worksheet;
}

MathEditLine* WorksheetLine::getMathEditLine() const
{
    return this->mainFrame->findChild<MathEditLine *>("MathEditLine");
}

void WorksheetLine::mousePressEvent(QMouseEvent *event)
{
    this->worksheet->setFocusedMathFrame(this);
    event->accept();
}

//void MathEditFrame::focusInEvent(QFocusEvent* e)
//{
//    std::cout << "fouces" << std::endl;
//    this->getWorksheet()->setFocusedMathFrame(this);
//}
