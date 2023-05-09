#ifndef WORKSHEETLINE_H
#define WORKSHEETLINE_H

#include <QWidget>
#include "fontmanager.h"
#include "worksheet.h"
#include "linetype.h"

class WorksheetLine: public QWidget
{
public:
    WorksheetLine(Worksheet* parentWorksheet, QWidget *parent = nullptr) : QWidget(parent), parentWorksheet(parentWorksheet) {};

    ~WorksheetLine() {
        destroy();
    }

    virtual void focus() = 0;
    virtual QString getText() = 0;
    virtual void setText(QString) = 0;
    virtual LineType getType() = 0;

    void destroy() {
        if (destroyed)
            return;

        removeChildren();

        destroyed = true;
    };

    void removeChildren() {
        for (WorksheetLine* c : children)
        {
            parentWorksheet->removeLine(c);
        }

        std::vector<WorksheetLine*>().swap(children);
    };

    void setParentLine(WorksheetLine* line) {
        parent = line;
        line->children.push_back(this);
    }

protected:
    Worksheet* parentWorksheet;
    WorksheetLine* parent = nullptr;
    std::vector<WorksheetLine*> children;
    bool destroyed = false;
};

#endif // WORKSHEETLINE_H
