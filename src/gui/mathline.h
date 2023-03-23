#ifndef MATHLINE_H
#define MATHLINE_H

#include "base/expression_parser/mathengine.h"
#include "worksheetline.h"
#include <QWidget>

class MathLine: public WorksheetLine
{
public:
    MathLine(QWidget *parent = nullptr) : WorksheetLine(parent) {};

    virtual void focus() = 0;
    virtual QString getText() = 0;
    LineType getType() { return LineType::Math; };
    virtual void onEvaluated(MathOutput) = 0;
};

#endif // MATHLINE_H
