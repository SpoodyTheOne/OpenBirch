#ifndef EXPONENTWIDGET_H
#define EXPONENTWIDGET_H

#include "mathcomponent.h"
#include <QWidget>

namespace Ui {
class ExponentWidget;
}

class ExponentWidget : public MathComponent
{
    Q_OBJECT

public:
    explicit ExponentWidget(QWidget *parent = nullptr);
    ~ExponentWidget();

private:
    Ui::ExponentWidget *ui;
};

#endif // EXPONENTWIDGET_H
