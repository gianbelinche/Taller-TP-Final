#include "ClientHandler.h"

#include <arpa/inet.h>

#include <cstdint>
#include <msgpack.hpp>
#include <sstream>

ClientHandler::ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                             std::atomic<uint32_t>& idAssigner,
                             ProtectedQueue<std::string>& incoming,
                             MessageDispatcher& msgDispatcher)
    : peer(std::move(p)),
      persistor(persist),
      map(worldMap),
      idGenerator(idAssigner),
      incomingMessages(incoming),
      dispatcher(msgDispatcher) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::vector<uint32_t> playerData = getCredentials();
  sendMap();

  ServerSender sender(peer, outgoingMessages);
  ServerReceiver receiver(peer, incomingMessages);
  outgoingMessages.disable();
  dispatcher.addPlayerQueue(playerData[1], &outgoingMessages);

  sender.start();
  receiver.start();
}

bool ClientHandler::finished() { return online; }

std::vector<uint32_t> ClientHandler::getCredentials() {
  std::string len_s = receiveMsg(sizeof(uint32_t));
  uint32_t len = *((uint32_t*)len_s.data());
  len = ntohl(len);

  std::string credentials = receiveMsg(len);

  std::vector<uint32_t> event;
  msgpack::object_handle oh =
      msgpack::unpack(credentials.data(), credentials.size());
  oh.get().convert(event);
  /* --- HARDCODEO --- */
  std::vector<uint32_t> resp = {10,0};
  std::stringstream buff;
  msgpack::pack(buff, resp);
  sendMsg(buff.str());
  return {2, 456, 2, 12345, 1523, 0, 2, 0, 0, 13};
}

void ClientHandler::sendMap() {
  sendTiles();
  sendTerrain();
  sendStructures();
}

void ClientHandler::sendMsg(std::string msg) {
  uint32_t msgLen = msg.size();
  msgLen = htonl(msgLen);
  char* msgLenS = (char*)&msgLen;

  peer.send(msgLenS, sizeof(uint32_t));  // Fixed size type, no problem
  peer.send(msg.data(), msg.size());
}

std::string ClientHandler::receiveMsg(uint32_t len) {
  std::vector<char> msgBuff(len);
  peer.recv(msgBuff.data(), len);
  std::string ss(msgBuff.begin(), msgBuff.end());
  return std::move(ss);
}

void ClientHandler::sendTiles() {
  std::stringstream mapBuffer;
  std::map<uint32_t, std::vector<std::string>>& tiles = map.getTiles();
  msgpack::pack(mapBuffer, tiles);
  sendMsg(mapBuffer.str());
}

void ClientHandler::sendTerrain() {
  std::stringstream mapBuffer;
  std::vector<std::vector<uint32_t>>& terrain = map.getTerrainMap();
  msgpack::pack(mapBuffer, terrain);
  sendMsg(mapBuffer.str());
}

void ClientHandler::sendStructures() {
  std::stringstream mapBuffer;
  std::vector<std::vector<uint32_t>>& structures = map.getStructuresMap();
  msgpack::pack(mapBuffer, structures);
  sendMsg(mapBuffer.str());
}
