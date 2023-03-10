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

    /**
     * @brief creates a new math edit frame with an empty math edit line inside.
     * @return a pointer to the created math frame object.
     */
    MathEditFrame* createNewMathEditWidget();

    /**
     * @brief finds the index of a specific math frame from the internal vector of math frames.
     * @param the math frame to find the index of.
     * @return an int representing the index. Will throw an error if it couldn't be found.
     */
    int getIndexOfMathFrame(MathEditFrame* mathFrame);

    /**
     * @brief finds the total number of math frames in this worksheet.
     * @return an int representing the total number of math frames in this worksheet.
     */
    int getTotalMathEdits();
private:
    Ui::Worksheet* ui;
    std::vector<MathEditFrame *> lines;
    QString savePath;
    QVBoxLayout* mainContentArea;
};

#endif // WORKSHEET_H
