#include "mainwindow.h"
#include "formulawidget.h"
#include "mathedit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MathEdit::createNew(ui->MainContentWindow);

    FormulaItem *f = new FormulaItem(ui->MainScrollArea);

    ui->mainScrollArea->addWidget(f);
}

MainWindow::~MainWindow()
{
    delete ui;
}
