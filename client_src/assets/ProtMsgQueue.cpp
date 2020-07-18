#include "../headers/ProtMsgQueue.h"

#include "../headers/QueueClosedException.h"
#include "../headers/OSError.h"

ProtMsgQueue::ProtMsgQueue() : closed(false) {}

void ProtMsgQueue::push(std::vector<uint32_t> &msg) {
    std::unique_lock<std::mutex> lk(mux);

    if (this->closed) {
        throw OSError("Error: se cerró inesperadamente la cola.");
    }

    this->queue.emplace(std::move(msg));
}

std::vector<uint32_t> ProtMsgQueue::pop() {
    std::unique_lock<std::mutex> lk(mux);

    if (this->closed) {
        throw QueueClosedException();
    }

    std::vector<uint32_t> element(std::move(this->queue.front()));
    this->queue.pop();
    return element;
}

void ProtMsgQueue::close() {
    std::unique_lock<std::mutex> lk(mux);
    this->closed = true;
}

bool ProtMsgQueue::isEmpty() {
    std::unique_lock<std::mutex> lk(mux);
    return this->queue.empty();
}

bool ProtMsgQueue::isClosed() {
    std::unique_lock<std::mutex> lk(mux);
    return this->closed;
}

ProtMsgQueue::~ProtMsgQueue() {}
