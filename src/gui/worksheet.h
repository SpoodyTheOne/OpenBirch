#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class Worksheet;
}

class Worksheet : public QWidget
{
    Q_OBJECT

    QVBoxLayout *MainContentArea;

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
