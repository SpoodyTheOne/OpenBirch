#ifndef MATHINPUTLINEEDIT_H
#define MATHINPUTLINEEDIT_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class MathInputLineEdit;
}

class MathInputLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit MathInputLineEdit(QWidget *parent = nullptr);
    ~MathInputLineEdit();

private:
    Ui::MathInputLineEdit *ui;
};

#endif // MATHINPUTLINEEDIT_H
