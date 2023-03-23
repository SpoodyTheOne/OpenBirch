#include "worksheet.h"
#include "ui_worksheet.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTabWidget>
#include <iostream>
#include <QFile>

Worksheet::Worksheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet)
{
    ui->setupUi(this);

    //WorksheetLine* newLine = createLine(0);
    //newLine->focus();
}

Worksheet::~Worksheet()
{
    delete ui;
}

WorksheetLine* Worksheet::createLine(int index, LineType type)
{

}

void Worksheet::focusFirst() {}

void Worksheet::focusLast() {}

bool Worksheet::save()
{
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), "");
    QFileDialog::Options options;
    options.setFlag(QFileDialog::Option::DontUseNativeDialog,false);
    QString file = QFileDialog::getSaveFileName(nullptr,tr("Save file"),"",tr("OpenBirch Worksheet File (*.obws);;All Files (*.*)"),nullptr,options);

    if (file.isEmpty())
        return false;

    if (!file.endsWith(".obws"))

    std::cout << file.toStdString() << std::endl;

    QStringList parts = file.split("/");
    QString name = parts.last().split(".").first();

    this->name = name;

    QTabWidget* parent = ((QTabWidget*)this->parentWidget()->parentWidget());
    parent->setTabText(parent->indexOf(this),name);

    // Convert lines array into json data, then save
    QStringList test = {"2x+4=4","Math","x=2","Output","3","Text","4","Text"};

    QFile fileHandle(file);
    fileHandle.open(QFile::WriteOnly);

    fileHandle.write(test.join("\n").toStdString().c_str());

    unsavedChanges = false;
    return true;
}

int Worksheet::close()
{
    if (!this->unsavedChanges) // if we dont have any unsaved changes just close
    {
        this->~Worksheet();
        return 0;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Unsaved Changes");
    msgBox.setText("Are you sure you want to close this?");
    msgBox.setStandardButtons(QMessageBox::Discard);
    msgBox.addButton(QMessageBox::Save);
    msgBox.addButton(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int reply = msgBox.exec();

    if (reply == QMessageBox::Discard)
        this->~Worksheet();
    else if (reply == QMessageBox::Save)
        this->save();

    return reply;
}
