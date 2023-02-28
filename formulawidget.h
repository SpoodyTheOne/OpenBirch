#ifndef FORMULAWIDGET_H
#define FORMULAWIDGET_H

#include <QWidget>

class FormulaItem
{
public:
    explicit FormulaItem(QString value) : m_value(value){}

    static const QString REGULAR_EXPRESSION;
    QPoint draw(const QPoint& pos, QPainter& p) const;

private:
    QString m_value;
};

class FormulaWidget : public QWidget
{
    Q_OBJECT
    using BaseClass = QWidget;
public:
    explicit FormulaWidget(QWidget* parent = nullptr);

public slots:
    void setFormula(const QString& formula);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QList<FormulaItem> m_items;
};

#endif // FORMULAWIDGET_H
