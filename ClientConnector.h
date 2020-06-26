#ifndef __CLIENT_CONNECTOR_H__
#define __CLIENT_CONNECTOR_H__

#include "Socket.h"
#include "Player.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "MessageQueue.h"

class ClientConnector {
    private:
        Socket socket;

    public:
        ClientConnector(const char *host, const char *service);
        ~ClientConnector();

        ClientConnector(const ClientConnector &copy) = delete;
        ClientConnector(ClientConnector&& other);
        ClientConnector& operator=(ClientConnector&& other);

        Player getPlayer(SDL_Renderer *renderer);
        MainMap getMainMap(SDL_Renderer *renderer);
        Sender getSender(MessageQueue &queue);
        Receiver getReceiver(MessageQueue &queue);
};

#endif
