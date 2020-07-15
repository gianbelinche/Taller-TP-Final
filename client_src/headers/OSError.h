#ifndef __OS_ERROR_H__
#define __OS_ERROR_H__

#define BUF_LEN 256
#include <typeinfo>

class OSError {
private:
    char msg_error[BUF_LEN];
public:
    explicit OSError(const char* fmt,...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~OSError() noexcept {}
};

#endif