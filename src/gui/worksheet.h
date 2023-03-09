#ifndef WORKSHEET_H
#define WORKSHEET_H

#include "matheditwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <mathedit.h>
#include <vector>

namespace Ui {
class Worksheet;
}

class Worksheet : public QWidget
{
    Q_OBJECT
public:
    explicit Worksheet(QWidget *parent = nullptr);
    ~Worksheet();

    QVBoxLayout* getMainContentArea() const;
    MathEditWidget* createNewMathEditWidget();
    int getIndexOfMathEdit(MathEditWidget* mathEdit);
    int getTotalMathEdits();
private:
    Ui::Worksheet* ui;
    std::vector<MathEditWidget *> lines;
    QString savePath;
    QVBoxLayout* mainContentArea;
};

#endif // WORKSHEET_H
