#include "mathedit.h"
#include "expressions.h"
#include "qlabel.h"

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

    std::string parsed = Expressions::instance().parseExpressionToString(this->text().toStdString());

    QLabel *label = new QLabel();

    label->setText(QString::fromStdString(parsed));

    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::transparent);
    palette.setColor(label->foregroundRole(), 0x81a1c1);
    label->setPalette(palette);

    label->setAlignment(Qt::AlignCenter);

    int index = this->layoutParent->indexOf(this);

    this->layoutParent->insertWidget( index + 1, label );

}


void MathEdit::createNew(QVBoxLayout *parent, int index) {
    MathEdit *mathEdit = new MathEdit();

    mathEdit->layoutParent = parent;

    parent->insertWidget(index,mathEdit);
    mathEdit->setFocus();
}


void MathEdit::createNewInSameParent(int index) {
    MathEdit::createNew( this->layoutParent, this->layoutParent->indexOf(this) + index );

    this->parentWidget()->parentWidget()->scroll(39845345,38954395);
}

void MathEdit::createNewInSameParent() {
    MathEdit::createNewInSameParent(1);
}

void MathEdit::parseAndCreateNew() {
    this->parseLine();
    this->createNewInSameParent(2);
}
