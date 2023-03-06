#include "mathedit.h"
#include "qlabel.h"
#include <iostream>
#include "mainwindow.h"

MathEdit::MathEdit(QWidget *parent) : QLineEdit(parent)
{

    //connect(this, &MathEdit::blockCountChanged, this, &MathEdit::updateLineNumberAreaWidth);
    //connect(this, &MathEdit::updateRequest, this, &MathEdit::updateLineNumberArea);
    //connect(this, &MathEdit::cursorPositionChanged, this, &MathEdit::highlightCurrentLine);
    connect(this, &MathEdit::returnPressed,this, &MathEdit::parseAndCreateNew);

    //highlightCurrentLine();
}

MathEdit::~MathEdit()
{
    delete outputLabel;
}

void MathEdit::resizeEvent(QResizeEvent *e)
{
    QLineEdit::resizeEvent(e);

    //QRect cr = contentsRect();
    //lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MathEdit::parseLine() {

    // std::string parsed = Expressions::instance().parseExpressionToString(this->text().toStdString());

    if (!outputLabel)
        outputLabel = new QLabel();

    outputLabel->setText(QString::fromStdString("Not Implemented :P"));

    QPalette palette = outputLabel->palette();
    palette.setColor(outputLabel->backgroundRole(), Qt::transparent);
    palette.setColor(outputLabel->foregroundRole(), 0x81a1c1);
    outputLabel->setPalette(palette);

    outputLabel->setAlignment(Qt::AlignCenter);

    int index = layoutParent->indexOf(this);

    layoutParent->insertWidget( index + 1, outputLabel );
}


MathEdit *MathEdit::createNew(QVBoxLayout *parent, int index) {
    MathEdit *mathEdit = new MathEdit();

    mathEdit->layoutParent = parent;

    parent->insertWidget(index,mathEdit);
    mathEdit->setFocus();

    return mathEdit;
}


void MathEdit::createNewInSameParent(int index) {
    MathEdit *newEdit = MathEdit::createNew( this->layoutParent, this->layoutParent->indexOf(this) + index );
}

void MathEdit::createNewInSameParent() {
    MathEdit::createNewInSameParent(1);
}

void MathEdit::parseAndCreateNew() {
    this->parseLine();

    if (this->parentWidget()->children().length() <= this->layoutParent->indexOf(this)+3)
        this->createNewInSameParent(2);
    else
        QWidget::focusNextChild();

}
