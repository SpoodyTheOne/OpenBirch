#include "mainwindow.h"
#include "mathedit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MathEdit::createNew(ui->MainContentWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}
