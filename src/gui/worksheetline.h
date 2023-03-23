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
    virtual void focus() = 0;
    virtual void getText() = 0;
    virtual void getType() = 0;
};

#endif // WORKSHEETLINE_H
