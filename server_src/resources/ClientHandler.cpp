#include "ClientHandler.h"

#include <arpa/inet.h>

#include <cstdint>
#include <msgpack.hpp>
#include <sstream>

ClientHandler::ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                             std::atomic<uint32_t>& idAssigner)
    : peer(std::move(p)),
      persistor(persist),
      map(worldMap),
      idGenerator(idAssigner) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::vector<uint32_t> playerData = getCredentials();
  sendMap();
}

bool ClientHandler::finished() { return online; }

std::vector<uint32_t> ClientHandler::getCredentials() {
  // Si el jugador no existe hacer idPlayer = idAssigner++; es todo atomico
  return {1, 2, 3};
}

void ClientHandler::sendMap() {
  std::stringstream mapBuffer;

  // Mando tiles
  std::map<uint32_t, std::vector<std::string>>& tiles = map.getTiles();
  msgpack::pack(mapBuffer, tiles);
  sendMsg(mapBuffer.str());
  mapBuffer.str("");  // Vacio el stream
  mapBuffer.clear();

  // Mando terrenos
  std::vector<std::vector<uint32_t>>& terrain = map.getTerrainMap();
  msgpack::pack(mapBuffer, terrain);
  sendMsg(mapBuffer.str());
  mapBuffer.str("");  // Vacio el stream
  mapBuffer.clear();

  // Mando estructuras
  std::vector<std::vector<uint32_t>>& structures = map.getStructuresMap();
  msgpack::pack(mapBuffer, structures);
  sendMsg(mapBuffer.str());
}

void ClientHandler::sendMsg(std::string msg) {
  uint32_t msgLen = msg.size();
  msgLen = htonl(msgLen);
  char* msgLenS = (char*)&msgLen;

  peer.send(msgLenS, sizeof(uint32_t));  // Fixed size type, no problem
  peer.send(msg.data(), msg.size());
}
