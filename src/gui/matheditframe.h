#ifndef MATHEDITFRAME_H
#define MATHEDITFRAME_H

#include <QFrame>
#include <QWidget>

namespace Ui {
class MathEditFrame;
}

class MathEditLine;

class MathEditFrame : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditFrame(QWidget *parent = nullptr);
    ~MathEditFrame();

    /**
     * @brief gets the frame in which the contents of the math edit is located.
     * @return pointer to the QFrame object
     */
    QFrame* getMainFrame() const;

    MathEditLine* getMathEditLine() const;

private:
    Ui::MathEditFrame *ui;
    QFrame* mainFrame;
};

#endif // MATHEDITFRAME_H
