#ifndef __QUIT_EXCEPTION_H__
#define __QUIT_EXCEPTION_H__

#include <typeinfo>

#define BUF_LEN 256

class QuitException : public std::exception {
private:
    char msg_error[BUF_LEN];
public:
    explicit QuitException(const char* fmt,...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~QuitException() noexcept {}
};

#endif
