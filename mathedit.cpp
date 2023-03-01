#include "mathedit.h"
#include "qlabel.h"
#include <iostream>

MathEdit::MathEdit(QWidget *parent) : QLineEdit(parent)
{

    //connect(this, &MathEdit::blockCountChanged, this, &MathEdit::updateLineNumberAreaWidth);
    //connect(this, &MathEdit::updateRequest, this, &MathEdit::updateLineNumberArea);
    //connect(this, &MathEdit::cursorPositionChanged, this, &MathEdit::highlightCurrentLine);
    connect(this, &MathEdit::returnPressed,this, &MathEdit::parseAndCreateNew);

    this->outputLabel = nullptr;

    //highlightCurrentLine();
}

void MathEdit::resizeEvent(QResizeEvent *e)
{
    QLineEdit::resizeEvent(e);

    //QRect cr = contentsRect();
    //lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void MathEdit::parseLine() {

    // std::string parsed = Expressions::instance().parseExpressionToString(this->text().toStdString());

    if (this->outputLabel == NULL)
        this->outputLabel = new QLabel();


    this->outputLabel->setText(QString::fromStdString("Not Implemented :P"));

    QPalette palette = this->outputLabel->palette();
    palette.setColor(this->outputLabel->backgroundRole(), Qt::transparent);
    palette.setColor(this->outputLabel->foregroundRole(), 0x81a1c1);
    this->outputLabel->setPalette(palette);

    this->outputLabel->setAlignment(Qt::AlignCenter);

    int index = this->layoutParent->indexOf(this);

    this->layoutParent->insertWidget( index + 1, this->outputLabel );

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

    this->parentWidget()->parentWidget()->scroll(39845345,38954395);
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
