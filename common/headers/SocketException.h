#ifndef SOCK_EX
#define SOCK_EX

#include <string>

class SocketException: public std::exception {
private:
    std::string msg_;

public:
    explicit SocketException(const std::string& message);
    const char* what() const throw() {
        return msg_.c_str();
    }
};

#endif
