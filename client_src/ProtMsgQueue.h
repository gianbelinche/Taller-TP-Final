#ifndef __PROTECTED_MESSAGE_QUEUE_H__
#define __PROTECTED_MESSAGE_QUEUE_H__

#include <vector>
#include <queue>
#include "stdint.h"
#include <mutex>
#include <condition_variable>

/*
 * Cola protegida de elementos tipo std::vector<uint32_t>
*/
class ProtMsgQueue {
    private:
        std::queue<std::vector<uint32_t>> queue;
        std::mutex mux;
        bool closed;
        
    public:
        ProtMsgQueue();
        ~ProtMsgQueue();

        ProtMsgQueue(const ProtMsgQueue &copy) = delete;

        void push(std::vector<uint32_t> &msg);
        std::vector<uint32_t> pop();
        void close();
        bool isEmpty();
        bool isClosed();
};

#endif
