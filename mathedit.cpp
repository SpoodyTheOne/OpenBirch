#include "mathedit.h"
#include "qlayout.h"
#include "mainwindow.h"
#include "exprtk.hpp"

MathEdit::MathEdit(QWidget *parent) : QLineEdit(parent)
{

    //connect(this, &MathEdit::blockCountChanged, this, &MathEdit::updateLineNumberAreaWidth);
    //connect(this, &MathEdit::updateRequest, this, &MathEdit::updateLineNumberArea);
    //connect(this, &MathEdit::cursorPositionChanged, this, &MathEdit::highlightCurrentLine);
    connect(this, &MathEdit::returnPressed,this, &MathEdit::parseAndCreateNew);

    //highlightCurrentLine();
}

void MathEdit::resizeEvent(QResizeEvent *e)
{
    QLineEdit::resizeEvent(e);

    //QRect cr = contentsRect();
    //lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MathEdit::parseLine() {



}


void MathEdit::createNew(QVBoxLayout *parent) {
    MathEdit *mathEdit = new MathEdit();

    mathEdit->layoutParent = parent;

    parent->addWidget(mathEdit);
    mathEdit->setFocus();
}


void MathEdit::createNewInSameParent() {
    MathEdit::createNew(this->layoutParent);

    this->parentWidget()->parentWidget()->scroll(39845345,38954395);
}

void MathEdit::parseAndCreateNew() {
    this->parseLine();
    this->createNewInSameParent();
}
