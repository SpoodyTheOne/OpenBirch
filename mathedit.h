#ifndef MATHEDIT_H
#define MATHEDIT_H

#include "qboxlayout.h"
#include "qobjectdefs.h"
#include "qlineedit.h"
#include "expressions.h"

class MathEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathEdit(QWidget *parent = nullptr);

    static void createNew(QVBoxLayout *parent = nullptr, int index = 0);

    void setLayoutParent(QVBoxLayout *parent) {
        layoutParent = parent;
    };

private:
    void resizeEvent(QResizeEvent *event) override;
    void createNewInSameParent(int index);

private slots:
    void parseLine();
    void createNewInSameParent();
    void parseAndCreateNew();

private:
    QVBoxLayout* layoutParent;
};

#endif // MATHEDIT_H
