#ifndef MATHEDIT_H
#define MATHEDIT_H

#include "qboxlayout.h"
#include "qobjectdefs.h"
#include "qlineedit.h"

class MathEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathEdit(QWidget *parent = nullptr);

    static void createNew(QVBoxLayout *parent = nullptr);

    void setLayoutParent(QVBoxLayout *parent) {
        layoutParent = parent;
    };

private:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void parseLine();
    void createNewInSameParent();
    void parseAndCreateNew();

private:
    QVBoxLayout* layoutParent;
};

#endif // MATHEDIT_H
