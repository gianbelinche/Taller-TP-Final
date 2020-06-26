#include "Sender.h"
#include "EmptyException.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <msgpack.hpp>

Sender::Sender(ClientConnector *aClConnector, MessageQueue *aQueue) : 
                                                    clConnector(aClConnector), 
                                                    queue(aQueue) {
}

Sender::~Sender() {}

Sender::Sender(Sender&& other) : Thread(std::move(other)), 
                                 clConnector(other.clConnector),
                                 queue(other.queue) {
    other.clConnector = nullptr;
    other.queue = nullptr;
}

Sender& Sender::operator=(Sender&& other) {
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

void Sender::run() {
    try {
        while (true) {
            //pop de la cola
            std::vector<uint32_t> event = queue->pop();

            //empaquetar
            std::stringstream buffer;
            msgpack::pack(buffer, event);
            std::string sbuffer = buffer.str();

            std::vector<char> msg(sbuffer.begin(), sbuffer.end());

            uint32_t len = msg.size();
            len = htonl(len);

            char *lenBuff = (char*)&len;
            std::vector<char> msgLen(4);

            for (int i = 0; i < 4; i++) {
                msgLen[i] = lenBuff[i];
            }

            //enviar largo
            clConnector->send(msgLen, len);

            //enviar paquete
            clConnector->send(msg, msg.size());
        }
    } catch(const EmptyException &e) {
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch(...) {
        std::cerr << "Error: unknown" << '\n';
    }

}
