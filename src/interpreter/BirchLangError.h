#ifndef BIRCHLANGERROR_H
#define BIRCHLANGERROR_H

#include <stdexcept>

namespace BirchLang {

class BirchLangError: public std::runtime_error
{
public:
    BirchLangError(const char* err, int occurance) : std::runtime_error(err)
    {
        this->what_msg = err;
        this->where = occurance;
    }

    const char* what()
    {
        return what_msg;
    }

private:
    const char* what_msg;
    int where;
};

}
#endif // BIRCHLANGERROR_H
