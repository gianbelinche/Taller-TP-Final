#include "BlockingMsgQueue.h"
#include "QueueClosedException.h"
#include "OSError.h"

BlockingMsgQueue::BlockingMsgQueue() : isClosed(false) {}

void BlockingMsgQueue::push(std::vector<uint32_t> &msg) {
    std::unique_lock<std::mutex> lk(mux);

    if (this->isClosed) {
        throw OSError("Error: se cerró inesperadamente la cola."); //chequear
    }

    this->queue.emplace(std::move(msg));
    this->condVar.notify_all();
}

std::vector<uint32_t> BlockingMsgQueue::pop() {
    std::unique_lock<std::mutex> lk(mux);

    while (this->queue.empty()) {
        if (this->isClosed) {
            throw QueueClosedException();
        }
        condVar.wait(lk);
    }

    std::vector<uint32_t> element(std::move(this->queue.front()));
    this->queue.pop();
    return std::move(element);
}

void BlockingMsgQueue::close() {
    std::unique_lock<std::mutex> lk(mux);
    this->isClosed = true;
    this->condVar.notify_all();
}

bool BlockingMsgQueue::isEmpty() {
    std::unique_lock<std::mutex> lk(mux);
    return this->queue.empty();
}

BlockingMsgQueue::~BlockingMsgQueue() {}
