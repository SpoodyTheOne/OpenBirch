#include "matheditline.h"
#include "base/postfixparser.h"
#include "base/expression_parser/mathengine.h"
#include "qevent.h"
#include "ui_matheditline.h"
#include "worksheet.h"
#include <iostream>
#include <thread>

MathEditLine::MathEditLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathEditLine)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);
    connect(getExpressionLine(), &MathExpressionLine::focussed, this, &MathEditLine::onFocus);
    connect(getExpressionLine(), &MathExpressionLine::changedLine, this, &MathEditLine::onChangeLine);
    connect(getExpressionLine(), &MathExpressionLine::removeLine, this, &MathEditLine::removeLine);
    connect(getExpressionLine(), &MathExpressionLine::returnPressed, this, &MathEditLine::returnPressed);
    connect(getExpressionLine(), &MathExpressionLine::textChanged, this, &MathEditLine::onExpressionChanged);
    std::cout << "Creating math edit..." << std::endl;

    getExpressionLine()->setFont(Worksheet::MathFont);

    QLabel *label = ui->inlineLabel;

    label->setFont(Worksheet::MathFont);
    label->setStyleSheet("QLabel { font-style: italic; color:#81a1c1; }");
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

Node* MathEditLine::getTreeRoot() const {
    return this->treeRoot;
}

void MathEditLine::returnPressed(QKeyEvent *event)
{   
    if (this->getWorksheet() == nullptr) {
        throw std::runtime_error("Tried to evalute expression but there is no reference to the parent worksheet!");
    }

    if (this->parentFrame == nullptr) {
        throw std::runtime_error("Tried to evaluate expression, but there is no reference to the math frame of this math line!");
    }

    bool showOnNewLine = !(event->modifiers() == Qt::AltModifier);
    bool createNewLine = event->modifiers() == Qt::ShiftModifier;

    // Evaluate expression
    this->evaluate(showOnNewLine);

    // If its the last math edit, then create a new one below
    if (createNewLine || this->getWorksheet()->getIndexOfMathFrame(this->parentFrame) == this->getWorksheet()->getTotalMathEdits() - 1) {
        int index = this->getWorksheet()->getIndexOfMathFrame(this->parentFrame);
        WorksheetLine* mathFrame = this->getWorksheet()->createNewMathEditWidget(index+1);
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

void MathEditLine::evaluate(bool showInline, bool keepTree) {
    MathEngine::AutoParse(
                this->getExpressionLine()->text(),
                this->getWorksheet()->getSymbolTable(),

                std::bind(
                    &MathEditLine::SolveFinish,
                    this,
                    std::placeholders::_1
                    )
                );
}

void MathEditLine::SolveFinish(MathOutput output)
{
    if (output.error && !output.error_msg.isEmpty()
            )
        this->getWorksheet()->addError(output.error_msg);
    else
        this->getWorksheet()->addCenteredText(output.output);
}

void MathEditLine::onExpressionChanged(const QString& text)
{
    // When expression is changed, set unevaluated flag to true,
    // so that things know that the expression is unevaluated
    this->unevaluatedChanges = true;
}

void MathEditLine::onChangeLine(int offset)
{
    if (offset < 0)
        this->getWorksheet()->focusPrevious();
    else
        this->getWorksheet()->focusNext();
}

void MathEditLine::removeLine() {
    this->getWorksheet()->removeMathEditWidget(this->parentFrame);
}
