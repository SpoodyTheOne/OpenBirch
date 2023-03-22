#ifndef ILINECONTENT_H
#define ILINECONTENT_H

#include <QString>

class ILineContent
{
public:
    virtual void focus() = 0;
    virtual QString getText() = 0;
};

#endif // ILINECONTENT_H
