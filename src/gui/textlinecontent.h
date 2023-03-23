#ifndef TEXTLINECONTENT_H
#define TEXTLINECONTENT_H

#include "ilinecontent.h"
#include <QWidget>

namespace Ui {
class TextLineContent;
}

class TextLineContent : public QWidget, public ILineContent
{
    Q_OBJECT

public:
    explicit TextLineContent(QWidget *parent = nullptr);
    ~TextLineContent();

    void focus();
    QString getText();

    void keyPressEvent(QKeyEvent);

private:
    Ui::TextLineContent *ui;
};

#endif // TEXTLINECONTENT_H
