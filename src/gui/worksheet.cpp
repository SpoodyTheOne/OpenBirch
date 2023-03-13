#include "worksheet.h"
#include "expression_tree_visualizer/expressiontreevisualizer.h"
#include "matheditline.h"
#include "qmenubar.h"
#include "ui_worksheet.h"
#include "mainwindow.h"
#include <iostream>
#include <QAction>

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

    connect(mathEditMenu->actions().first(), &QAction::triggered, this, &Worksheet::showExpressionTree);
}

Worksheet::~Worksheet()
{
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
}

MathEditFrame* Worksheet::getFocusedMathFrame() {
    return this->focusedMathFrame;
}

void Worksheet::showExpressionTree()
{
    MathEditLine* mathEdit = this->focusedMathFrame->getMathEditLine();
    std::cout << "Showing expression tree for: " << mathEdit->objectName().toStdString() << std::endl;
    Node* treeRoot{};

    // Eavaluate the expression if its not already up to date
    if (mathEdit->unevaluatedChanges)
        mathEdit->evaluate();

    treeRoot = mathEdit->parser.getTreeRoot();

    // If theres still no expression tree after evaluation, something must be wrong
    if (!treeRoot)
    {
        throw std::runtime_error("No root node for expression tree after evaluation.");
    }

    ExpressionTreeVisualizer* treeVisualizer = new ExpressionTreeVisualizer;
    treeVisualizer->visualizeExpressionTree(treeRoot);
    treeVisualizer->show();
    std::cout << "root node: " <<treeRoot << std::endl;
}

void Worksheet::addCenteredText(QString text)
{
    QLabel *label = new QLabel();

    label->setText(text);

    this->getFocusedMathFrame()->getMainFrame()->layout()->addWidget(label);
}
