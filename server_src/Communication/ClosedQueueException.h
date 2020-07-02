#ifndef QUE_EX
#define QUE_EX

#include <string>

class ClosedQueueException: public std::exception {
private:
    std::string msg_;

public:
    explicit ClosedQueueException(const std::string& message);
    const char* what() const throw() {
        return msg_.c_str();
    }
};

#endif
