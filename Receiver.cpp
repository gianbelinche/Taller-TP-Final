#include "Receiver.h"
#include <exception>
#include <iostream>
#include "SocketException.h"
#include <arpa/inet.h>
#include <msgpack.hpp>

Receiver::Receiver(ClientConnector *aClConnector, MessageQueue *aQueue) : 
                                                    clConnector(aClConnector), 
                                                    queue(aQueue) {}

Receiver::~Receiver() {
    if (queue) queue->close();
}

Receiver::Receiver(Receiver&& other) : Thread(std::move(other)),
                                       clConnector(other.clConnector), 
                                       queue(other.queue) {
    other.clConnector = nullptr;
    other.queue = nullptr;
}

Receiver& Receiver::operator=(Receiver&& other) {
    if (this == &other) {
        return *this;
    }

    Thread::operator=(std::move(other));

    clConnector = other.clConnector;
    other.clConnector = nullptr;
    queue = other.queue;
    other.queue = nullptr;

    return *this;
}

void Receiver::run() {
    try {
        while (true) {
            //recibe largo
            std::vector<char> lenBuff = clConnector->receive(4);
            uint32_t len = (lenBuff[3] << 24) + (lenBuff[2] << 16) +
                           (lenBuff[1] << 8) + lenBuff[0];

            len = ntohl(len);

            //recibe paquete
            std::vector<char> msgBuff = clConnector->receive(len);
            std::string ss(msgBuff.begin(), msgBuff.end());

            //desempaqueta
            std::vector<uint32_t> event;
            msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
            oh.get().convert(event);

            //push a la cola
            queue->push(event);
        }
    } catch(const SocketException &e) {
        queue->close();
        queue = nullptr;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch(...) {
        std::cerr << "Error: unknown" << '\n';
    }
}
