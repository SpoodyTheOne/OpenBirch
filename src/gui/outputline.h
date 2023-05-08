#ifndef OUTPUTLINE_H
#define OUTPUTLINE_H

#include "worksheetline.h"
#include <QWidget>

namespace Ui {
class OutputLine;
}

class OutputLine : public WorksheetLine
{
    Q_OBJECT

public:
    explicit OutputLine(Worksheet* parentWorksheet, QWidget *parent = nullptr);
    ~OutputLine();

private:
    Ui::OutputLine *ui;
};

#endif // OUTPUTLINE_H
