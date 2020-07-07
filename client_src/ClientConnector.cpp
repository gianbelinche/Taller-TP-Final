#include "ClientConnector.h"
#include "SocketException.h"
#include <arpa/inet.h>

#include <map>
#include <msgpack.hpp>
#include <string>
#include <sstream>

ClientConnector::ClientConnector() {}

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

void ClientConnector::connect(const char *host, const char *service){
    socket.connect(host, service);
}

void ClientConnector::closeSocket() {
    socket.shutdown_close();
}

uint32_t ClientConnector::receiveLen() {
    char lenBuff[4];
    socket.recv(lenBuff, 4);

    uint32_t len = *((uint32_t*)lenBuff);

    return ntohl(len);
}

std::string ClientConnector::receiveMsg(uint32_t len) {
    std::vector<char> msgBuff(len);
    socket.recv(&msgBuff[0], len);
    std::string msgStr(msgBuff.begin(), msgBuff.end());

    return msgStr;
}

Player ClientConnector::getPlayer(SDL_Renderer *renderer,GraphicInventory& inventory) {
    uint32_t len = receiveLen();
    std::string msgStr = std::move(receiveMsg(len));

    std::vector<uint32_t> msg;
    msgpack::object_handle oh = msgpack::unpack(msgStr.data(), msgStr.size());
    oh.get().convert(msg);

    Player player(renderer, (PlayerRace)msg[2], msg[1], msg[3], msg[4], msg[5],
                  (EquipType)msg[6], (EquipType)msg[7], (EquipType)msg[8], 
                  (EquipType)msg[9]);

    inventory.equip(msg[6]); 
    inventory.equip(msg[7]); 
    inventory.equip(msg[8]); 
    inventory.equip(msg[9]);              

    return player;
}

MainMap ClientConnector::getMainMap(SDL_Renderer *renderer) {
    //Recibo tiles
    uint32_t tileLen = receiveLen();
    std::string tMsgStr = std::move(receiveMsg(tileLen));

    std::map<uint32_t, std::vector<std::string>> tiles;
    msgpack::unpack(tMsgStr.data(), tMsgStr.size()).get().convert(tiles);

    //Recibo matriz de terreno
    uint32_t matLen0 = receiveLen();
    std::string mMsgStr0 = std::move(receiveMsg(matLen0));

    std::vector<std::vector<uint32_t>> matrixLayer0;
    msgpack::unpack(mMsgStr0.data(), mMsgStr0.size()).get().convert(matrixLayer0);

    //Recibo matriz de estructuras
    uint32_t matLen1 = receiveLen();
    std::string mMsgStr1 = std::move(receiveMsg(matLen1));
    
    std::vector<std::vector<uint32_t>> matrixLayer1;
    msgpack::object_handle ohM1 = msgpack::unpack(mMsgStr1.data(), mMsgStr1.size());
    ohM1.get().convert(matrixLayer1);

    //Genero MainMap
    MainMap mainMap(tiles, renderer, matrixLayer0, matrixLayer1);
    return mainMap;
}

void ClientConnector::sendReceivedSignal(ClientProtocol &clientProtocol, uint32_t ID) {
    std::vector<uint32_t> event = std::move(clientProtocol.makeMsgConnection(ID));
    
    //empaquetar
    std::stringstream buffer;
    msgpack::pack(buffer, event);
    std::string sbuffer = buffer.str();

    std::vector<char> msg(sbuffer.begin(), sbuffer.end());

    uint32_t len = htonl(msg.size());

    //enviar largo
    this->send((char*)&len, 4);

    //enviar paquete
    this->send(msg, msg.size());
}

Sender ClientConnector::getSender(BlockingMsgQueue &queue) {
    Sender sender(this, &queue);
    return sender;
}

Receiver ClientConnector::getReceiver(ProtMsgQueue &queue) {
    Receiver receiver(this, &queue);
    return receiver;
}

std::vector<char> ClientConnector::receive(uint32_t len) {
    std::vector<char> msg(len);
    if (socket.recv(&msg[0], len) < len) {
        throw SocketException("Error al recibir: Se cerró socket.");
    }
    return msg;
}

void ClientConnector::send(char *msg, uint32_t len) {
    socket.send(msg, len);
}

void ClientConnector::send(std::vector<char> &msg, uint32_t len) {
    socket.send(&msg[0], len);
}
