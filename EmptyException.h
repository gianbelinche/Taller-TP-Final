#ifndef __EMPTY_EXCEPTION_H__
#define __EMPTY_EXCEPTION_H__

#include <exception>

class EmptyException : public std::exception {
    public:
        EmptyException() noexcept;
        virtual ~EmptyException() noexcept;
        virtual const char* what() const noexcept;
};

#endif
