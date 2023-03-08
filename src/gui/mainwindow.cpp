#include "mainwindow.h"
#include "mathedit.h"
#include "ui_mainwindow.h"

Ui::MainWindow mainUi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MathEdit::createNew(ui->MainContentWindow);

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
