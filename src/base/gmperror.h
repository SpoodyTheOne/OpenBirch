#ifndef GMPERROR_H
#define GMPERROR_H

#include <stdexcept>

class GmpError : public std::runtime_error
{
public:
    GmpError(const char* e) : std::runtime_error(e) {}
};

#endif // GMPERROR_H
