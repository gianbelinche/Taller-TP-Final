#ifndef __JSON_ERROR_H__
#define __JSON_ERROR_H__

#include <typeinfo>

#define BUF_LEN 256

class JsonError : public std::exception {
    private:
        char msg_error[BUF_LEN];

    public:
        explicit JsonError(const char* fmt,...) noexcept;
        virtual const char *what() const noexcept;
        virtual ~JsonError() noexcept {}
};

#endif
