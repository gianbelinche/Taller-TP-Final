#ifndef CLASS_SDLERROR
#define CLASS_SDLERROR

#define BUF_LEN 256
#include <typeinfo>

class SDLError : public std::exception {
private:
    char msg_error[BUF_LEN];
public:
    explicit SDLError(const char* fmt,...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~SDLError() noexcept {}
};

#endif
