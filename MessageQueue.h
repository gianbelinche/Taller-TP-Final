#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <vector>
#include <queue>
#include "stdint.h"
#include <mutex>
#include <condition_variable>

/*
 * Cola bloqueante de elementos tipo std::vector<uint32_t>
*/
class MessageQueue {
    private:
        std::queue<std::vector<uint32_t>> queue;
        std::mutex mux;
        std::condition_variable condVar;
        bool isClosed;
        
    public:
        MessageQueue();
        ~MessageQueue();

        MessageQueue(const MessageQueue &copy) = delete;
        MessageQueue(MessageQueue&& other);
        MessageQueue& operator=(MessageQueue&& other);

        void push(std::vector<uint32_t> &msg);
        std::vector<uint32_t> pop();
        void close();
        bool isEmpty();
};

#endif
