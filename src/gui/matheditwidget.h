#ifndef MATHEDITWIDGET_H
#define MATHEDITWIDGET_H

#include <QWidget>

namespace Ui {
class MathEditWidget;
}

class Worksheet;

class MathEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditWidget(QWidget *parent = nullptr);
    ~MathEditWidget();

    friend Worksheet;
private slots:
    void on_expressionLine_returnPressed();

private:
    Ui::MathEditWidget *ui;
    Worksheet* worksheet;

    void evaluate();
};

#endif // MATHEDITWIDGET_H
