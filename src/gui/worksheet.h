#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QWidget>

namespace Ui {
class Worksheet;
}

class Worksheet : public QWidget
{
    Q_OBJECT

public:
    explicit Worksheet(QWidget *parent = nullptr);
    ~Worksheet();

    void focusFirst();
    void focusLast();
    int close();
    bool save();

    QString getName();

    inline static QFont MathFont;

private:
    Ui::Worksheet *ui;
    QString name = "New Worksheet";
    bool unsavedChanges = false;
    std::vector<QWidget> lines;
};

#endif // WORKSHEET_H
