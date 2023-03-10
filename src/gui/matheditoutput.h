#ifndef MATHEDITOUTPUT_H
#define MATHEDITOUTPUT_H

#include <QWidget>

namespace Ui {
class MathEditOutput;
}

class MathEditOutput : public QWidget
{
    Q_OBJECT

public:
    explicit MathEditOutput(QWidget *parent = nullptr);
    ~MathEditOutput();

private:
    Ui::MathEditOutput *ui;
};

#endif // MATHEDITOUTPUT_H
