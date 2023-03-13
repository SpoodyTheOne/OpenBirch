#ifndef MATHRENDERERWIDGET_H
#define MATHRENDERERWIDGET_H

#include <QWidget>

namespace Ui {
class MathRendererWidget;
}

class MathRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MathRendererWidget(QWidget *parent = nullptr);
    ~MathRendererWidget();

private:
    Ui::MathRendererWidget *ui;
};

#endif // MATHRENDERERWIDGET_H
