#include "Receiver.h"

Receiver::Receiver(Socket *aSocket, MessageQueue &aQueue) : socket(aSocket), 
                                                            queue(aQueue) {}

Receiver::~Receiver() {
    queue.close();
}

Receiver::Receiver(Receiver&& other) : socket(other.socket), queue(other.queue) {
    other.socket = nullptr;
}

Receiver& Receiver::operator=(Receiver&& other) {
    //COMPLETAR
}

void Receiver::run() {
    try {
            while (true) {
                
            }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    //recibe largo
    //recibe paquete
    //desempaqueta
    //push a la cola
    //cerrar cuando SocketException
}
