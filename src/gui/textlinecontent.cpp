#include "textlinecontent.h"
#include "ui_textlinecontent.h"

TextLineContent::TextLineContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextLineContent)
{
    ui->setupUi(this);
}

TextLineContent::~TextLineContent()
{
    delete ui;
}
