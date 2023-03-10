#ifndef MATHEDIT_H
#define MATHEDIT_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qobjectdefs.h"
#include "qlineedit.h"

class MathEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathEdit(QWidget *parent = nullptr);
    ~MathEdit();

    static MathEdit *createNew(QVBoxLayout *parent = nullptr, int index = 0);

    void setLayoutParent(QVBoxLayout *parent) {
        layoutParent = parent;
    };

    QLabel *outputLabel = nullptr;

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
