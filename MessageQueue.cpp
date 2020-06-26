#include "MessageQueue.h"
#include "EmptyException.h"

MessageQueue::MessageQueue() : isClosed(false) {}

void MessageQueue::push(std::vector<uint32_t> &msg) {
    std::unique_lock<std::mutex> lk(mux);
    this->queue.emplace(std::move(msg));
    this->condVar.notify_all();
}

std::vector<uint32_t> MessageQueue::pop() {
    std::unique_lock<std::mutex> lk(mux);

    while (this->queue.empty()) {
        if (this->isClosed) {
            throw EmptyException();
        }
        condVar.wait(lk);
    }

    std::vector<uint32_t> element(std::move(this->queue.front()));
    this->queue.pop();
    return std::move(element);
}

void MessageQueue::close() {
    std::unique_lock<std::mutex> lk(mux);
    this->isClosed = true;
    this->condVar.notify_all();
}

bool MessageQueue::isEmpty() {
    std::unique_lock<std::mutex> lk(mux);
    return this->queue.empty();
}

MessageQueue::~MessageQueue() {}
