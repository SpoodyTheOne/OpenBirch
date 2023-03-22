#ifndef WORKSHEETLINE_H
#define WORKSHEETLINE_H

#include <QWidget>

enum LineType {
    Text,
    Math,
    Output
};

class Worksheet;

namespace Ui {
class WorksheetLine;
}

class WorksheetLine : public QWidget
{
    Q_OBJECT

public:
    explicit WorksheetLine(QWidget *parent = nullptr);
    ~WorksheetLine();

    void setWorksheet(Worksheet* worksheet);
    void focus();

    void addWidget();

    LineType getType() { return type; }

private:
    Ui::WorksheetLine *ui;
    LineType type;
};

#endif // WORKSHEETLINE_H
