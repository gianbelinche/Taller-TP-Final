#ifndef __CLIENT_CONNECTOR_H__
#define __CLIENT_CONNECTOR_H__

class ClientConnector;

#include "Socket.h"
#include "Player.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "BlockingMsgQueue.h"
#include "ProtMsgQueue.h"
#include <vector>

class ClientConnector {
    private:
        Socket socket;
        uint32_t receiveLen();
        std::string receiveMsg(uint32_t len);

    public:
        ClientConnector(const char *host, const char *service);
        ~ClientConnector();

        ClientConnector(const ClientConnector &copy) = delete;
        ClientConnector(ClientConnector&& other);
        ClientConnector& operator=(ClientConnector&& other);

        void closeSocket();

        Player getPlayer(SDL_Renderer *renderer);
        MainMap getMainMap(SDL_Renderer *renderer);
        Sender getSender(BlockingMsgQueue &queue);
        Receiver getReceiver(ProtMsgQueue &queue);

        std::vector<char> receive(uint32_t len);
        void send(std::vector<char> &msg, uint32_t len);
};

#endif