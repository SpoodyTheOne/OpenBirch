#include "worksheet.h"
#include "expression_tree_visualizer/expressiontreevisualizer.h"
#include "matheditline.h"
#include "qmenubar.h"
#include "ui_worksheet.h"
#include "mainwindow.h"
#include <iostream>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>
#include <qstyle.h>

Worksheet::Worksheet(MainWindow *_mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet),
    mainWindow{_mainWindow}
{
    ui->setupUi(this);

    this->mainContentArea = ui->MainContentWindow;

    // Create start edit field, when its a new empty worksheet
    this->createNewMathEditWidget();

//    QAction* mathEditMenu = ;
    QMenu* mathEditMenu = this->mainWindow->getMenuBar()->findChild<QMenu *>("menuMathEdit");

    connect(mathEditMenu->actions().at(0), &QAction::triggered, this, &Worksheet::showExpressionTree);
    connect(mathEditMenu->actions().at(1), &QAction::triggered, this, &Worksheet::evaluateFocusedMathEdit);
}

Worksheet::~Worksheet()
{
    std::cout << "Worksheet destroyed" << std::endl;

    for (auto line : lines) {
        delete line;
    }

    delete ui;
}

QVBoxLayout* Worksheet::getMainContentArea() const
{
    return mainContentArea;
}

WorksheetLine* Worksheet::createNewMathEditWidget(int index)
{
    QVBoxLayout* parent = this->mainContentArea;
    int idx = index == -1 ? this->lines.size() : index;
    if (parent == nullptr) {
        throw std::runtime_error("No parent layout while creating new math edit widget.");
    }

    if (idx < 0)
    {
        throw std::runtime_error("Index was negative while creating new math edit widget.");
    }

    WorksheetLine* mathFrameParent = new WorksheetLine();
    QFrame* mathFrame = mathFrameParent->getMainFrame();
    MathEditLine* mathLine = new MathEditLine();

    mathFrame->layout()->addWidget(mathLine); // Insert the math edit line into the math frame's layout

    // Make sure the math edit knows what worksheets it's in
    mathFrameParent->worksheet = this;
    mathLine->parentFrame = mathFrameParent;

    // Store reference in worksheets record of lines
    this->lines.push_back(mathFrameParent);
    parent->insertWidget(idx, mathFrameParent);

    ui->scrollArea->verticalScrollBar()->setValue(mathFrameParent->y());

    return mathFrameParent;
}

void Worksheet::removeMathEditWidget(WorksheetLine *mathFrame)
{
    if (lines.size() == 1) // focusLastMathEdit() creates a new line if there are none
    {
        // So clear the line instead and pretend.
        mathFrame->getMathEditLine()->getExpressionLine()->setText("");
        return;
    }

    int index = fmax(getIndexOfMathFrame(mathFrame) - 1,0);

    lines.erase(std::remove(lines.begin(), lines.end(), mathFrame), lines.end());
    delete mathFrame;

    setFocusedMathFrame(lines[index]);
}

int Worksheet::getTotalMathEdits()
{
    return this->lines.size();
}

int Worksheet::getIndexOfMathFrame(WorksheetLine* mathFrame)
{
    // TODO: Dont use QWidget::idnexOf, this will break once we add more types of line.
    // Alternative: change getIndexOfMathFrame to getIndexOfLine and have it work for all types of lines

    if (this->mainContentArea == nullptr) {
        throw std::runtime_error("No parent layout where mathedits are inserted into.");
    }

    int idx = this->mainContentArea->indexOf(mathFrame);
    if (idx < 0) {
        throw std::runtime_error("Math edit not found in layout. This might be because the math edit is not part of this worksheet.");
    }
    return idx;
}

void Worksheet::setFocusedMathFrame(WorksheetLine* mathFrame)
{
    this->focusedMathFrame = mathFrame;

    // Enable or disable math edit menu when math frames are focused
    QMenu* mathEditMenu = this->mainWindow->getMenuBar()->findChild<QMenu *>("menuMathEdit");
    if (mathFrame)
        mathEditMenu->setEnabled(true);
    else if (mathEditMenu->isHidden()) // If the focus is on the menu itself don't hide it
        mathEditMenu->setEnabled(false);

    if (this->focusedMathFrame != nullptr)
        this->focusedMathFrame->getMathEditLine()->getExpressionLine()->setFocus();
}

WorksheetLine* Worksheet::getFocusedMathFrame() {
    return this->focusedMathFrame;
}

void Worksheet::focusPrevious() {
    size_t index = getIndexOfMathFrame(getFocusedMathFrame())-1;

    if (index < 0 || index >= lines.size())
        return;

    setFocusedMathFrame(lines[index]);
}

void Worksheet::focusNext() {
    size_t index = getIndexOfMathFrame(getFocusedMathFrame())+1;

    std::cout << index << std::endl;

    if (index < 0 || index >= lines.size())
        return;

    setFocusedMathFrame(lines[index]);
}

void Worksheet::showExpressionTree()
{
    MathEditLine* mathEdit = this->focusedMathFrame->getMathEditLine();
    std::cout << "Showing expression tree for: " << mathEdit->objectName().toStdString() << std::endl;

    // Evaluate with keepTree true so we can visualize it
    mathEdit->evaluate(true,true);

    Node* treeRoot = mathEdit->getTreeRoot();

    // If theres still no expression tree after evaluation, something must be wrong
    if (!treeRoot)
    {
        throw std::runtime_error("No root node for expression tree after evaluation.");
    }
    std::cout << "root node: " <<treeRoot << std::endl;
    ExpressionTreeVisualizer* treeVisualizer = new ExpressionTreeVisualizer(treeRoot);
    treeVisualizer->visualizeExpressionTree();
    treeVisualizer->show();
}

void Worksheet::evaluateFocusedMathEdit() {
    this->getFocusedMathFrame()->getMathEditLine()->evaluate();
}

void Worksheet::addCenteredText(QString text)
{
    std::cout << "adding centered text" << std::endl;

    QLabel *label = new QLabel();

    label->setText(text);

    label->setFont(Worksheet::MathFont);

    label->setStyleSheet("QLabel { font-style: italic; color:#81a1c1; }");

    this->getFocusedMathFrame()->getMainFrame()->layout()->addWidget(label);
}

void Worksheet::addError(QString err)
{
    QLabel *label = new QLabel();

    label->setText(err);

    label->setFont(Worksheet::MathFont);

    label->setStyleSheet("QLabel { font-style: italic; color:#bf616a; }");

    this->getFocusedMathFrame()->getMainFrame()->layout()->addWidget(label);
}

void Worksheet::focusLastMathEdit()
{
    if (this->lines.size() == 0)
        this->createNewMathEditWidget();

    this->setFocusedMathFrame(lines[lines.size()-1]);
}

void Worksheet::mousePressEvent(QMouseEvent *event)
{
    focusLastMathEdit();
    event->accept();
}

SymbolTable *Worksheet::getSymbolTable()
{
    return &symbolTable;
}
