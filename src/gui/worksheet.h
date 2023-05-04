#ifndef WORKSHEET_H
#define WORKSHEET_H

#include "base/expression_parser/environment.h"
#include "base/symboltable/symboltable.h"
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

    WorksheetLine* createLine(int index,LineType type = LineType::Math);
    void evaluateLine(MathLine*);

    QString getName();

    Environment* getGlobalEnvironment();

    inline static QFont MathFont;

private:
    Ui::Worksheet *ui;
    QString name = "New Worksheet";
    bool unsavedChanges = false;
    std::vector<QWidget> lines;
    Environment* globalEnvironment = 0;
};

#endif // WORKSHEET_H
