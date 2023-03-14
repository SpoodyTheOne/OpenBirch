#include "worksheet.h"
#include "expression_tree_visualizer/expressiontreevisualizer.h"
#include "matheditline.h"
#include "qmenubar.h"
#include "ui_worksheet.h"
#include "mainwindow.h"
#include <iostream>
#include <QAction>
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

MathEditFrame* Worksheet::createNewMathEditWidget()
{
    QVBoxLayout* parent = this->mainContentArea;
    int idx = this->lines.size();
    if (parent == nullptr) {
        throw std::runtime_error("No parent layout while creating new math edit widget.");
    }

    if (idx < 0)
    {
        throw std::runtime_error("Index was negative while creating new math edit widget.");
    }

    MathEditFrame* mathFrameParent = new MathEditFrame();
    QFrame* mathFrame = mathFrameParent->getMainFrame();
    MathEditLine* mathLine = new MathEditLine();

    mathFrame->layout()->addWidget(mathLine); // Insert the math edit line into the math frame's layout

    // Make sure the math edit knows what worksheets it's in
    mathFrameParent->worksheet = this;
    mathLine->parentFrame = mathFrameParent;

    // Store reference in worksheets record of lines
    this->lines.push_back(mathFrameParent);

    parent->insertWidget(idx, mathFrameParent);
    return mathFrameParent;
}

int Worksheet::getTotalMathEdits()
{
    return this->lines.size();
}

int Worksheet::getIndexOfMathFrame(MathEditFrame* mathFrame)
{


    if (this->mainContentArea == nullptr) {
        throw std::runtime_error("No parent layout where mathedits are inserted into.");
    }

    int idx = this->mainContentArea->indexOf(mathFrame);
    if (idx < 0) {
        throw std::runtime_error("Math edit not found in layout. This might be because the math edit is not part of this worksheet.");
    }
    return idx;
}

void Worksheet::setFocusedMathFrame(MathEditFrame* mathFrame)
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

MathEditFrame* Worksheet::getFocusedMathFrame() {
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
    Node* treeRoot{};

    // Eavaluate the expression if its not already up to date
    if (mathEdit->unevaluatedChanges)
    {           std::cout << "unsaved changes!" << std::endl;

        mathEdit->evaluate();}

    treeRoot = mathEdit->getTreeRoot();

    // If theres still no expression tree after evaluation, something must be wrong
    if (!treeRoot)
    {
        throw std::runtime_error("No root node for expression tree after evaluation.");
    }
    std::cout << "root node: " <<treeRoot << std::endl;
    ExpressionTreeVisualizer* treeVisualizer = new ExpressionTreeVisualizer;
    treeVisualizer->visualizeExpressionTree(treeRoot);
    treeVisualizer->show();

}

void Worksheet::evaluateFocusedMathEdit() {
    this->getFocusedMathFrame()->getMathEditLine()->evaluate();
}

void Worksheet::addCenteredText(QString text)
{
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

void Worksheet::mousePressEvent(QMouseEvent *event) {

    this->setFocusedMathFrame(lines[lines.size()-1]);

    event->accept();
}
