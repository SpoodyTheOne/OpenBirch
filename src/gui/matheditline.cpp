#include "matheditline.h"
#include "base/expression_parser/postfix_parser/postfixparser.h"
#include "qevent.h"
#include "ui_matheditline.h"
#include "worksheet.h"
#include <iostream>

MathEditLine::MathEditLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditLine)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);
    connect(getExpressionLine(), &MathExpressionLine::focussed, this, &MathEditLine::onFocus);
    connect(getExpressionLine(), &MathExpressionLine::textChanged, this, &MathEditLine::onExpressionChanged);
    std::cout << "Creating math edit..." << std::endl;
}

MathEditLine::~MathEditLine()
{
    std::cout << "Destroying math edit widget..." << std::endl;
    delete ui;
}

Worksheet* MathEditLine::getWorksheet() const {
    return this->parentFrame->getWorksheet();
}

MathExpressionLine* MathEditLine::getExpressionLine() {
    return this->findChild<MathExpressionLine *>("expressionLine");
}

void MathEditLine::on_expressionLine_returnPressed()
{
    if (this->getWorksheet() == nullptr) {
        throw std::runtime_error("Tried to evalute expression but there is no reference to the parent worksheet!");
    }

    if (this->parentFrame == nullptr) {
        throw std::runtime_error("Tried to evaluate expression, but there is no reference to the math frame of this math line!");
    }

    // Evaluate expression
    this->evaluate();

    // If its the last math edit, then create a new one below
    if (this->getWorksheet()->getIndexOfMathFrame(this->parentFrame) == this->getWorksheet()->getTotalMathEdits() - 1) {
        MathEditFrame* mathFrame = this->getWorksheet()->createNewMathEditWidget();
        mathFrame->getMathEditLine()->getExpressionLine()->setFocus();
    }
    else
    {
        // Focus math edit below
        QWidget::focusNextChild();
    }
}

void MathEditLine::onFocus(bool focused)
{
    if (focused) // Set the focused math frame to this one
        this->getWorksheet()->setFocusedMathFrame(this->parentFrame);
    else // When not focused anymore, reset focused math frame
        this->getWorksheet()->setFocusedMathFrame(nullptr);
}

void MathEditLine::evaluate()
{
    MathExpressionLine* expressionLine = this->getExpressionLine();
    std::cout << expressionLine->text().toStdString() << std::endl;
    parser.setExpression(expressionLine->text());
    parser.compile();
    QString output = parser.evaluate();
    this->unevaluatedChanges = false;


    std::string postfix = PostFixParser::parseExpression(expressionLine->text().toStdString());

    this->getWorksheet()->addCenteredText(QString(postfix.c_str()));
}

void MathEditLine::onExpressionChanged(const QString& text)
{
    // When expression is changed, set unevaluated flag to true,
    // so that things know that the expression is unevaluated
    this->unevaluatedChanges = true;
}
