#ifndef MATHEDITFRAME_H
#define MATHEDITFRAME_H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MathEditFrame;
}

class MathEditLine;
class Worksheet;

class MathEditFrame : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditFrame(QWidget *parent = nullptr);
    ~MathEditFrame();

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
    Ui::MathEditFrame *ui;
    QFrame* mainFrame;
    Worksheet* worksheet;
};

#endif // MATHEDITFRAME_H
