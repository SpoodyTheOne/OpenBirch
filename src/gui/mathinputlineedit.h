#ifndef MATHINPUTLINEEDIT_H
#define MATHINPUTLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QEvent>

class MathInputLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathInputLineEdit(QWidget* parent = 0);
    ~MathInputLineEdit();

    void focusInEvent(QFocusEvent *e);

signals:
    void focused();
};

#endif // MATHINPUTLINEEDIT_H
