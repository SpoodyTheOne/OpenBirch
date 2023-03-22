#ifndef WORKSHEETLINE_H
#define WORKSHEETLINE_H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class WorksheetLine;
}

class MathEditLine;
class Worksheet;

class WorksheetLine : public QWidget
{
    Q_OBJECT

public:
    explicit WorksheetLine(QWidget *parent = nullptr);
    ~WorksheetLine();

    /**
     * @brief gets the frame in which the contents of the math edit is located.
     * @return pointer to the QFrame object in this math frame.
     */
    QFrame* getMainFrame() const;

    /**
     * @brief gets the math edit line of the math frame. The object where the math expression is written in.
     * @return pointer to the MathEditLine object in this math frame.
     */
    MathEditLine* getMathEditLine() const;

    Worksheet* getWorksheet() const;

    void mousePressEvent(QMouseEvent *event);

    friend Worksheet;
protected:
//    void focusInEvent(QFocusEvent* e) override;

private:
    Ui::WorksheetLine *ui;
    QFrame* mainFrame;
    Worksheet* worksheet;
};

#endif // WORKSHEETLINE_H
