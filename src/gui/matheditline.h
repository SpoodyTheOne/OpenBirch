#ifndef MATHEDITLINE_H
#define MATHEDITLINE_H

#include <QWidget>

namespace Ui {
class MathEditLine;
}

class Worksheet;

class MathEditLine : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditLine(QWidget *parent = nullptr);
    ~MathEditLine();

    friend Worksheet;
private slots:
    void on_expressionLine_returnPressed();

private:
    Ui::MathEditLine *ui;
    Worksheet* worksheet;

    void evaluate();
};

#endif // MATHEDITLINE_H