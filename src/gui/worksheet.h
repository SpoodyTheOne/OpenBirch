#ifndef WORKSHEET_H
#define WORKSHEET_H

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

    QVBoxLayout *MainContentArea;

    QString savePath;
    std::vector<MathEdit> lines;

public:
    QVBoxLayout* mainContentArea() {
        return MainContentArea;
    }
    explicit Worksheet(QWidget *parent = nullptr);
    ~Worksheet();

private:
    Ui::Worksheet *ui;
};

#endif // WORKSHEET_H
