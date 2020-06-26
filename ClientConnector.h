#ifndef __CLIENT_CONNECTOR_H__
#define __CLIENT_CONNECTOR_H__

#include "Socket.h"
#include "Player.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "MessageQueue.h"
#include <vector>

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

        std::vector<char> receive(uint32_t len);
        void send(std::vector<char> msg, uint32_t len);
};

#endif
