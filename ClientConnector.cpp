#include "ClientConnector.h"
#include <arpa/inet.h>

#include <map>
#include <msgpack.hpp>
#include <string>
#include <sstream>

ClientConnector::ClientConnector(const char *host, const char *service) {
    socket.connect(host, service);
}

ClientConnector::~ClientConnector() {}

ClientConnector::ClientConnector(ClientConnector&& other) : 
                                            socket(std::move(other.socket)) {}

ClientConnector& ClientConnector::operator=(ClientConnector&& other) {
    if (this == &other) {
        return *this;
    }

    socket = std::move(other.socket);
    return *this;
}

Player ClientConnector::getPlayer(SDL_Renderer *renderer) {
    char lenBuff[4];
    socket.recv(lenBuff, 4);

    uint32_t len = (lenBuff[3] << 24) + (lenBuff[2] << 16) + 
                   (lenBuff[1] << 8) + lenBuff[0];

    len = ntohl(len);

    std::vector<char> msgBuff(len);
    socket.recv(&msgBuff[0], len);

    std::string ss(msgBuff.begin(), msgBuff.end());

    std::vector<uint32_t> msg;
    msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
    oh.get().convert(msg);

    Player player(renderer, (PlayerRace)msg[2], msg[1], (uint16_t)msg[3], 
                    (uint16_t)msg[4], (bool)msg[5]); //chequear

    return std::move(player);
}

MainMap ClientConnector::getMainMap(SDL_Renderer *renderer) {
    //chequear funcion
    char lenBuff[4];
    socket.recv(lenBuff, 4);

    uint32_t len = (lenBuff[3] << 24) + (lenBuff[2] << 16) + 
                   (lenBuff[1] << 8) + lenBuff[0];

    len = ntohl(len);

    std::vector<char> msgBuff(len);
    socket.recv(&msgBuff[0], len);
    std::string ss(msgBuff.begin(), msgBuff.end());

    std::map<uint32_t, std::vector<std::string>> tiles;
    msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
    oh.get().convert(tiles);

    socket.recv(lenBuff, 4);
    len = (lenBuff[3] << 24) + (lenBuff[2] << 16) + (lenBuff[1] << 8) + 
          lenBuff[0];

    len = ntohl(len);

    msgBuff = std::vector<char>(len);
    socket.recv(&msgBuff[0], len);
    ss = std::string(msgBuff.begin(), msgBuff.end());

    std::vector<std::vector<uint32_t>> matrixLayer0;
    oh = msgpack::unpack(ss.data(), ss.size());
    oh.get().convert(matrixLayer0);

    socket.recv(lenBuff, 4);
    len = (lenBuff[3] << 24) + (lenBuff[2] << 16) + (lenBuff[1] << 8) + 
          lenBuff[0];

    len = ntohl(len);

    msgBuff = std::vector<char>(len);
    socket.recv(&msgBuff[0], len);
    ss = std::string(msgBuff.begin(), msgBuff.end());
    
    std::vector<std::vector<uint32_t>> matrixLayer1;
    oh = msgpack::unpack(ss.data(), ss.size());
    oh.get().convert(matrixLayer1);

    MainMap mainMap(tiles, renderer, matrixLayer0, matrixLayer1);
    return std::move(mainMap);
}

Sender ClientConnector::getSender(MessageQueue &queue) {
    Sender sender(this, &queue);
    return std::move(sender);
}

Receiver ClientConnector::getReceiver(MessageQueue &queue) {
    Receiver receiver(this, &queue);
    return std::move(receiver);
}

std::vector<char> ClientConnector::receive(uint32_t len) {
    std::vector<char> msg(len);
    socket.recv(&msg[0], len);
    return std::move(msg);
}

void ClientConnector::send(std::vector<char> msg, uint32_t len) {
    socket.send(&msg[0], len);
}
