#ifndef __SENDER_H__
#define __SENDER_H__

#include "Socket.h"
#include "MessageQueue.h"
#include "Thread.h"

class Sender : public Thread {
    private:
        Socket *socket;
        MessageQueue &queue;

    public:
        Sender(Socket *aSocket, MessageQueue &aQueue);
        ~Sender();

        Sender(const Sender &copy) = delete;
        Sender(Sender&& other);
        Sender& operator=(Sender&& other);

        void run();
};

#endif
