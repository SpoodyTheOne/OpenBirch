#include "mainwindow.h"
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
    mainUi = *ui;

    // Create new empty worksheet when opened
    this->createNewWorksheet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMenuBar* MainWindow::getMenuBar() const {
    return ui->menuBar;
}

void MainWindow::on_actionQuit_triggered()
{
    QWidget::close();
}

void MainWindow::on_actionNew_Tab_triggered()
{
    this->createNewWorksheet();
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
    QString file = QFileDialog::getSaveFileName(nullptr,"Save file","",".obw",nullptr,options);

    QStringList parts = file.split("/");
    QString name = parts.last().split(".").first();

    mainUi.tabWidget->setTabText(mainUi.tabWidget->currentIndex(),name);
}

Worksheet* MainWindow::createNewWorksheet()
{
    Worksheet *newWorksheet = new Worksheet();
    newWorksheet->mainWindow = this;

    ui->tabWidget->addTab(newWorksheet,"*New Worksheet");
    mainUi.tabWidget->setCurrentWidget(newWorksheet);
    return newWorksheet;
}


void MainWindow::on_actionAdd_Exponent_triggered()
{

}

