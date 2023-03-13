#ifndef EXPONENTWIDGET_H
#define EXPONENTWIDGET_H

#include <QWidget>

namespace Ui {
class ExponentWidget;
}

class ExponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExponentWidget(QWidget *parent = nullptr);
    ~ExponentWidget();

private:
    Ui::ExponentWidget *ui;
};

#endif // EXPONENTWIDGET_H
