#ifndef MATHRENDERERWIDGET_H
#define MATHRENDERERWIDGET_H

#include "mathcomponent.h"
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

    void addComponent(MathComponent component);
};

#endif // MATHRENDERERWIDGET_H
