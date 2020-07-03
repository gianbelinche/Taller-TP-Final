#ifndef __QUEUE_CLOSED_EXCEPTION_H__
#define __QUEUE_CLOSED_EXCEPTION_H__

#include <exception>

class QueueClosedException : public std::exception {
    public:
        QueueClosedException() noexcept;
        virtual ~QueueClosedException() noexcept;
        virtual const char* what() const noexcept;
};

#endif
