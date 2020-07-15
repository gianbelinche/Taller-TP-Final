#include "../headers/OSError.h"
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdarg>

OSError::OSError(const char* fmt,...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_error, BUF_LEN, fmt, args);
    va_end(args);

    msg_error[BUF_LEN-1] = 0;
}

const char * OSError::what() const noexcept {
    return this->msg_error;
}
