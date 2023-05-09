#ifndef MATHINPUT_H
#define MATHINPUT_H

#include "mathline.h"
#include <QWidget>
#include "worksheet.h"

namespace Ui {
class MathInput;
}

class MathInput : public MathLine
{
    Q_OBJECT

public:
    explicit MathInput(Worksheet* worksheet, QWidget *parent = nullptr);
    ~MathInput();

    void focus();
    QString getText();
    void setText(QString);
    LineType getType() { return LineType::Text; }

    void onEvaluated(MathOutput);

    void evaluate();

private:
    Ui::MathInput *ui;
};

#endif // MATHINPUT_H
