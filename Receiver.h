#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "MessageQueue.h"
#include "ClientConnector.h"
#include "Thread.h"

class Receiver : public Thread {
    private:
        ClientConnector *clConnector;
        MessageQueue *queue;

    public:
        Receiver(ClientConnector *aClConnector, MessageQueue *aQueue);
        ~Receiver();

        Receiver(const Receiver &copy) = delete;
        Receiver(Receiver&& other);
        Receiver& operator=(Receiver&& other);

        void run();
};

#endif
