#ifndef WORKSHEETLINE_H
#define WORKSHEETLINE_H

#include <QWidget>

enum LineType
{
    Math,
    Text,
    Output
};

class WorksheetLine: public QWidget
{
public:
    WorksheetLine(QWidget *parent = nullptr) : QWidget(parent) {};

    virtual void focus() = 0;
    virtual QString getText() = 0;
    virtual LineType getType() = 0;
};

#endif // WORKSHEETLINE_H
