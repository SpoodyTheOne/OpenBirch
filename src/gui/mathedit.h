#ifndef MATHEDIT_H
#define MATHEDIT_H

#include "base/expression_parser/parser.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qobjectdefs.h"
#include "qlineedit.h"

class MathEdit : public QLineEdit
{
    Q_OBJECT

public:
    MathEdit(QWidget *parent = nullptr);
    ~MathEdit();

    static MathEdit *createNew(QVBoxLayout *parent = nullptr, int index = 0);

    void setLayoutParent(QVBoxLayout *parent) {
        layoutParent = parent;
    };

    QLabel *outputLabel = nullptr;
    Parser* getExpressionParser() { return m_expressionParser; }
    void focusInEvent(QFocusEvent* event) override;
private:
    Parser* m_expressionParser;
    void resizeEvent(QResizeEvent *event) override;
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
