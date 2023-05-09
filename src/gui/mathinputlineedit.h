#ifndef MATHINPUTLINEEDIT_H
#define MATHINPUTLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QFocusEvent>


class MathInputLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit MathInputLineEdit(QWidget *parent = nullptr);
    ~MathInputLineEdit();
    void focusInEvent(QFocusEvent*);

signals:
    void onFocused();
};

#endif // MATHINPUTLINEEDIT_H
