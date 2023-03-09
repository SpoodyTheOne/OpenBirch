#ifndef MATHEDIT_H
#define MATHEDIT_H

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "base/expression_parser/parser.h"

class MathEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathEdit(QWidget *parent = nullptr);
    ~MathEdit();

    QLabel *outputLabel{};
    static MathEdit *createNew(QVBoxLayout *parent = nullptr, int index = 0);
protected:
    void focusInEvent(QFocusEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Parser* m_ExpressionParser;

    void createNewInSameParent(int index);
    static void ShowParserTree(const Tree* const tree);
    inline static MathEdit* focused = nullptr;
    void onKeyPress(QKeyEvent e);
private slots:
    void parseLine();
    void createNewInSameParent();
    void parseAndCreateNew();


private:
    QVBoxLayout* layoutParent;
};

#endif // MATHEDIT_H
