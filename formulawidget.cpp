#include "formulawidget.h"
#include <QRegularExpression>
#include <QPainter>
#include <QStyleOption>


const QString FormulaItem::REGULAR_EXPRESSION = "sqrt\\((?<value>\\d+)\\)";

QPoint FormulaItem::draw(const QPoint& pos, QPainter& p) const
{
    int valueWidth = p.fontMetrics().width(m_value);
    int valueHeight = p.fontMetrics().height();

    p.drawLine(pos.x(), 4 + valueHeight / 2, pos.x() + 5, 4 + valueHeight);
    p.drawLine(pos.x() + 5, 4 + valueHeight, pos.x() + 10, pos.y() + 1);
    p.drawLine(pos.x() + 10, pos.y() + 1, pos.x() + 14 + valueWidth, pos.y() + 1);

    p.drawText(QRect(pos.x() + 12, pos.y() + 4, pos.x() + 12 + valueWidth, pos.y() + 4 + valueHeight), m_value);
    return QPoint(pos.x() + valueWidth + 20, pos.y());
}

FormulaWidget::FormulaWidget(QWidget* parent) :
    BaseClass(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void FormulaWidget::setFormula(const QString& formula)
{
    m_items.clear();

    QRegularExpression sqrt_value(FormulaItem::REGULAR_EXPRESSION);
    QRegularExpressionMatchIterator i = sqrt_value.globalMatch(formula);

    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch())
        {
            m_items.append(FormulaItem(match.captured("value")));
        }
    }

    update();
}

void FormulaWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::black);

    QPoint formulaPos(2, 2);

    for (const FormulaItem& item : m_items)
    {
        formulaPos = item.draw(formulaPos, p);
    }
}
