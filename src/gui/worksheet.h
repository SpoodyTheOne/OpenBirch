#ifndef WORKSHEET_H
#define WORKSHEET_H

#include "matheditframe.h"
#include <QWidget>
#include <QVBoxLayout>
#include <mathexpressionline.h>
#include <vector>
#include <QMessageBox>
#include <QMouseEvent>

namespace Ui {
class Worksheet;
}

class MainWindow;

class Worksheet : public QWidget
{
    Q_OBJECT
public:
    explicit Worksheet(MainWindow* _mainWindow, QWidget *parent = nullptr);
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

    static inline QFont MathFont;

    void setFocusedMathFrame(MathEditFrame* mathFrame);

    void focusPrevious();
    void focusNext();

    MathEditFrame *getFocusedMathFrame();

    void addCenteredText(QString text);
    void addError(QString);

    void mousePressEvent(QMouseEvent *event);

    friend class MainWindow;

    int destroy() {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Unsaved Changes");
        msgBox.setText("Are you sure you want to close this?");
        msgBox.setStandardButtons(QMessageBox::Discard);
        msgBox.addButton(QMessageBox::Save);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        int reply = msgBox.exec();

        if(reply == QMessageBox::Discard)
            this->~Worksheet();

        return reply;
    }
private:
    Ui::Worksheet* ui{};
    std::vector<MathEditFrame *> lines;
    QString savePath;
    QVBoxLayout* mainContentArea{};
    MainWindow* mainWindow{};
    MathEditFrame* focusedMathFrame{};


private slots:
    void showExpressionTree();
    void evaluateFocusedMathEdit();
};

#endif // WORKSHEET_H
