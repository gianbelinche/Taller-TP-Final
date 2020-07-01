#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver;

#include "ProtMsgQueue.h"
#include "ClientConnector.h"
#include "Thread.h"

class Receiver : public Thread {
    private:
        ClientConnector *clConnector;
        ProtMsgQueue *queue;

    public:
        Receiver(ClientConnector *aClConnector, ProtMsgQueue *aQueue);
        ~Receiver();

        Receiver(const Receiver &copy) = delete;
        Receiver(Receiver&& other);
        Receiver& operator=(Receiver&& other);

        void run();
};

#endif
