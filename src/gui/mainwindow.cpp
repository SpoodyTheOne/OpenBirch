#include "mainwindow.h"
#include "mathedit.h"
#include "ui_mainwindow.h"
#include "worksheet.h"
#include <iostream>
#include <QFileDialog>

Ui::MainWindow mainUi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Worksheet *newWorksheet = new Worksheet();

    ui->tabWidget->addTab(newWorksheet,"*New Worksheet");

    MathEdit::createNew(newWorksheet->mainContentArea());

    mainUi = *ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QWidget::close();
}

void MainWindow::on_actionNew_Tab_triggered()
{
    Worksheet *newWorksheet = new Worksheet();

    MathEdit::createNew(newWorksheet->mainContentArea());

    mainUi.tabWidget->addTab(newWorksheet,"*New Worksheet");
    mainUi.tabWidget->setCurrentWidget(newWorksheet);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    mainUi.tabWidget->removeTab(index);
}


void MainWindow::on_actionClose_Worksheet_triggered()
{
    mainUi.tabWidget->removeTab(mainUi.tabWidget->currentIndex());
}


void MainWindow::on_actionSave_triggered()
{
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), "");
    QFileDialog::Options options;
    options.setFlag(QFileDialog::Option::DontUseNativeDialog,false);
    QFileDialog::getSaveFileName(nullptr,"Save file","",".obw",nullptr,options);
}

