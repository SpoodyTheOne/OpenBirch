#ifndef WORKSHEETLINE_H
#define WORKSHEETLINE_H

#include <QWidget>
#include "fontmanager.h"

class Worksheet;

enum LineType
{
    Math,
    Text,
    Output
};

class WorksheetLine: public QWidget
{
public:
    WorksheetLine(Worksheet* parentWorksheet, QWidget *parent = nullptr) : QWidget(parent), parentWorksheet(parentWorksheet) {};

    virtual void focus() = 0;
    virtual QString getText() = 0;
    virtual LineType getType() = 0;

protected:
    Worksheet* parentWorksheet;
};

#endif // WORKSHEETLINE_H
