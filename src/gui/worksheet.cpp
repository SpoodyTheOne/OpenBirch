#include "worksheet.h"
#include "ui_worksheet.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTabWidget>

Worksheet::Worksheet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Worksheet)
{
    ui->setupUi(this);
}

Worksheet::~Worksheet()
{
    delete ui;
}


void Worksheet::focusFirst() {}

void Worksheet::focusLast() {}

bool Worksheet::save()
{
    //QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), "");
    QFileDialog::Options options;
    options.setFlag(QFileDialog::Option::DontUseNativeDialog,false);
    QString file = QFileDialog::getSaveFileName(nullptr,"Save file","",".ows",nullptr,options);

    if (file.isEmpty())
        return false;

    QStringList parts = file.split("/");
    QString name = parts.last().split(".").first();

    this->name = name;

    QTabWidget* parent = ((QTabWidget*)this->parentWidget()->parentWidget());
    parent->setTabText(parent->indexOf(this),name);

    // Convert lines array into json data, then save

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
