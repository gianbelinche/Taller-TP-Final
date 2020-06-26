#ifndef __SENDER_H__
#define __SENDER_H__

#include "ClientConnector.h"
#include "MessageQueue.h"
#include "Thread.h"

class Sender : public Thread {
    private:
        ClientConnector *clConnector;
        MessageQueue *queue;

    public:
        Sender(ClientConnector *aClConnector, MessageQueue *aQueue);
        ~Sender();

        Sender(const Sender &copy) = delete;
        Sender(Sender&& other);
        Sender& operator=(Sender&& other);

        void run();
};

#endif
