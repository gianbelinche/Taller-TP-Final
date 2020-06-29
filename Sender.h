#ifndef __SENDER_H__
#define __SENDER_H__

class Sender;

#include "ClientConnector.h"
#include "BlockingMsgQueue.h"
#include "Thread.h"

class Sender : public Thread {
    private:
        ClientConnector *clConnector;
        BlockingMsgQueue *queue;

    public:
        Sender(ClientConnector *aClConnector, BlockingMsgQueue *aQueue);
        ~Sender();

        Sender(const Sender &copy) = delete;
        Sender(Sender&& other);
        Sender& operator=(Sender&& other);

        void run();
};

#endif
