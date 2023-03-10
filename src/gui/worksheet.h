#ifndef WORKSHEET_H
#define WORKSHEET_H

#include "matheditframe.h"
#include "matheditline.h"
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
    MathEditFrame* createNewMathEditWidget();
    int getIndexOfMathEdit(MathEditFrame* mathEdit);
    int getTotalMathEdits();
private:
    Ui::Worksheet* ui;
    std::vector<MathEditFrame *> lines;
    QString savePath;
    QVBoxLayout* mainContentArea;
};

#endif // WORKSHEET_H
