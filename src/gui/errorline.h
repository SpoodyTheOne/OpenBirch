#ifndef ERRORLINE_H
#define ERRORLINE_H

#include "worksheetline.h"
#include <QWidget>

namespace Ui {
class ErrorLine;
}

class ErrorLine : public WorksheetLine
{
    Q_OBJECT

public:
    explicit ErrorLine(Worksheet* parentWorksheet, QWidget *parent = nullptr);
    ~ErrorLine();

    void focus();
    QString getText();
    void setText(QString);
    LineType getType();

private:
    Ui::ErrorLine *ui;
};

#endif // ERRORLINE_H
