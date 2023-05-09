#ifndef WORKSHEET_H
#define WORKSHEET_H

#include "base/expression_parser/environment.h"
#include "mathline.h"
#include "worksheetline.h"
#include <QWidget>
#include "worksheetline.h"

namespace Ui {
class Worksheet;
}

class Worksheet : public QWidget
{
    Q_OBJECT

public:
    explicit Worksheet(QWidget *parent = nullptr);
    ~Worksheet();

    int close();
    bool save();

    void focusFirst();
    void focusLast();

    WorksheetLine* createLineRelative(LineType type = LineType::Math, WorksheetLine* parent = nullptr, int offset = 0, bool focus = false);
    WorksheetLine* createLine(int index = 0,LineType type = LineType::Math);

    bool isAtEnd();

    void setFocusedLine(WorksheetLine*);

    void evaluateLine(MathLine*);

    QString getName();

    Environment* getGlobalEnvironment();

private:
    Ui::Worksheet *ui;
    QString name = "New Worksheet";
    bool unsavedChanges = false;

    int currentLineIdx = -1;
    WorksheetLine* currentLine;

    std::vector<QWidget> lines;
    Environment* globalEnvironment = 0;
};

#endif // WORKSHEET_H
