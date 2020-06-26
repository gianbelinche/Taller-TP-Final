#include "Thread.h"
#include <utility>

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {} 

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}


Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
