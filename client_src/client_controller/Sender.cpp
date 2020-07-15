#include "../headers/Sender.h"
#include "../headers/QueueClosedException.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <msgpack.hpp>
#include <SDL2/SDL.h>

Sender::Sender(ClientConnector *aClConnector, BlockingMsgQueue *aQueue) : 
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
            std::vector<uint32_t> event = std::move(queue->pop());

            //empaquetar
            std::stringstream buffer;
            msgpack::pack(buffer, event);
            std::string sbuffer = buffer.str();

            std::vector<char> msg(sbuffer.begin(), sbuffer.end());

            uint32_t len = htonl(msg.size());

            //enviar largo
            clConnector->send((char*)&len, 4);

            //enviar paquete
            clConnector->send(msg, msg.size());
        }
    } catch(const QueueClosedException &e) {
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    } catch(const std::exception& e) {
        std::cerr << "Sender: ";
        std::cerr << e.what() << '\n';
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    } catch(...) {
        std::cerr << "Sender: ";
        std::cerr << "Error Sender: unknown" << '\n';
        SDL_Event sdlevent;
        sdlevent.type = SDL_QUIT;
        SDL_PushEvent(&sdlevent);
    }

}
