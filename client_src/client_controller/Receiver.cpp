#include "../headers/Receiver.h"
#include <exception>
#include <iostream>
#include "../headers/SocketException.h"
#include <arpa/inet.h>
#include <msgpack.hpp>

Receiver::Receiver(ClientConnector *aClConnector, ProtMsgQueue *aQueue) : 
                                                    clConnector(aClConnector), 
                                                    queue(aQueue) {}

Receiver::~Receiver() {}

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
            std::vector<char> lenBuff = std::move(clConnector->receive(4));

            uint32_t len = *((uint32_t*)&lenBuff[0]);
            len = ntohl(len);

            //recibe paquete
            std::vector<char> msgBuff = std::move(clConnector->receive(len));
            std::string ss(msgBuff.begin(), msgBuff.end());

            //desempaqueta
            std::vector<uint32_t> event;
            msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
            oh.get().convert(event);

            //push a la cola
            queue->push(event);
        }
    } catch(const SocketException &e) {
        // Se cerro correctamente
        queue->close();
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    } catch(const std::exception& e) {
        // Se cerro inesperadamente
        std::cerr << "Receiver: " << '\n';
        std::cerr << e.what() << '\n';
        queue->close();
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    } catch(...) {
        // Se cerro inesperadamente
        std::cerr << "Receiver: " << '\n';
        std::cerr << "Error Receiver: unknown" << '\n';
        queue->close();
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    }
}
