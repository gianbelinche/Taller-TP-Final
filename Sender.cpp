#include "Sender.h"

Sender::Sender(Socket *aSocket, MessageQueue &aQueue) : socket(aSocket), 
                                                        queue(aQueue) {
}

Sender::~Sender() {}

Sender::Sender(Sender&& other) {
    //COMPLETAR
}

Sender& Sender::operator=(Sender&& other) {
    //COMPLETAR
}

void Sender::run() {
    //pop de la cola
    //empaquetar
    //enviar largo
    //enviar paquete
    //cerrar cuando EmptyException de la cola 
}
