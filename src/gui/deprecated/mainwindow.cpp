#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include "worksheet.h"
#include <iostream>
#include <QFileDialog>
#include <QEvent>
#include <QMessageBox>
#include "matheditline.h"
#include <QFontDatabase>

Ui::MainWindow mainUi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainUi = *ui;

    QString font = ":/fonts/Latinmodernmath-Regular.otf";
    int id = QFontDatabase::addApplicationFont(font);

    std::cout << QDir::currentPath().toStdString() << std::endl;

    if (id == -1) {
        std::cout << "Failed to load math font" << std::endl;

        QFile fontFile(font);
        fontFile.open(QFile::ReadOnly);
        std::cout << fontFile.exists() << std::endl;
        std::cout << fontFile.size() << std::endl;
    }
    else
    {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont monospace(family);

        Worksheet::MathFont = monospace;
    }

    // Create new empty worksheet when opened
    this->createNewWorksheet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (;;) {
        Worksheet* tab = (Worksheet*)ui->tabWidget->widget(0);

        if (tab == nullptr)
            break;

        if (tab->destroy() == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }

    event->accept();
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

void closeTab(int index)
{
    ((Worksheet*)mainUi.tabWidget->widget(index))->destroy();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeTab(index);
}


void MainWindow::on_actionClose_Worksheet_triggered()
{
    closeTab(mainUi.tabWidget->currentIndex());
}


void MainWindow::on_actionSave_triggered()
{
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), "");
    QFileDialog::Options options;
    options.setFlag(QFileDialog::Option::DontUseNativeDialog,false);
    QString file = QFileDialog::getSaveFileName(nullptr,"Save file","",".obw",nullptr,options);

    if (file.isEmpty())
        return;

    QStringList parts = file.split("/");
    QString name = parts.last().split(".").first();

    mainUi.tabWidget->setTabText(mainUi.tabWidget->currentIndex(),name);
}

Worksheet* MainWindow::createNewWorksheet()
{
    Worksheet *newWorksheet = new Worksheet(this);

    ui->tabWidget->addTab(newWorksheet,"*New Worksheet");
    mainUi.tabWidget->setCurrentWidget(newWorksheet);

    newWorksheet->lines[0]->getMathEditLine()->getExpressionLine()->setFocus();

    return newWorksheet;
}

