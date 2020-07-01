#ifndef __BLOCKING_MESSAGE_QUEUE_H__
#define __BLOCKING_MESSAGE_QUEUE_H__

#include <vector>
#include <queue>
#include "stdint.h"
#include <mutex>
#include <condition_variable>

/*
 * Cola bloqueante de elementos tipo std::vector<uint32_t>
*/
class BlockingMsgQueue {
    private:
        std::queue<std::vector<uint32_t>> queue;
        std::mutex mux;
        std::condition_variable condVar;
        bool isClosed;
        
    public:
        BlockingMsgQueue();
        ~BlockingMsgQueue();

        BlockingMsgQueue(const BlockingMsgQueue &copy) = delete;
        BlockingMsgQueue(BlockingMsgQueue&& other);
        BlockingMsgQueue& operator=(BlockingMsgQueue&& other);

        void push(std::vector<uint32_t> &msg);
        std::vector<uint32_t> pop();
        void close();
        bool isEmpty();
};

#endif
