#ifndef TESTTEXTINPUT_H
#define TESTTEXTINPUT_H

#include "mathline.h"
#include <QWidget>

class Worksheet;

namespace Ui {
class TestTextInput;
}

class TestTextInput : public MathLine
{
    Q_OBJECT

public:
    explicit TestTextInput(QWidget *parent = nullptr);
    ~TestTextInput();

    void focus();
    QString getText();
    LineType getType() { return LineType::Text; }

    void onEvaluated(MathOutput);

    void evaluate();

private:
    Ui::TestTextInput *ui;
};

#endif // TESTTEXTINPUT_H
