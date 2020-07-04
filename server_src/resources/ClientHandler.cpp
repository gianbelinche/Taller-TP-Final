#include "../headers/ClientHandler.h"

#include <arpa/inet.h>

#include <cstdint>
#include <iostream>
#include <msgpack.hpp>
#include <sstream>
#include <unistd.h>

ClientHandler::ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                             std::atomic<uint32_t>& idAssigner,
                             ProtectedQueue<std::string>& incoming,
                             MessageDispatcher& msgDispatcher, GameState& state,
                             ServerEventListener& eventListener)
    : peer(std::move(p)),
      persistor(persist),
      online(true),
      map(worldMap),
      idGenerator(idAssigner),
      incomingMessages(incoming),
      dispatcher(msgDispatcher),
      world(state),
      listener(eventListener) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::vector<uint32_t> playerData = {2, 1550, 1, 2500, 2500, 0, 2, 11, 15, 13};
  std::stringstream buffPlaydata;
  msgpack::pack(buffPlaydata, playerData);
  sendMsg(buffPlaydata.str());
  // getCredentials();
  sendMap();

  ServerSender sender(peer, outgoingMessages);
  ServerReceiver receiver(peer, incomingMessages);
  // outgoingMessages.disable();
  dispatcher.addPlayerQueue(playerData[1], &outgoingMessages);
  /* --- HARDCODEO --- */

  Class* cl1 = new Class(0, 1, 2, 3);
  Race* r1 = new Race(0, 100, 1, 2);
  PlayerNet* player1 =
      new PlayerNet(2500, 2500, 1550, world, 100, 50, 6, 200, 2, 90, nullptr,
                    nullptr, nullptr, nullptr, &PlayerState::normal, cl1, r1);

  world.addPlayer(player1);
  sender.start();
  receiver.start();
  usleep(10000000);
  MonsterType* mt = new MonsterType(20, 10);
  Monster* monst = mt->newMonster(20, 2500, 2700, 1, world, listener);
  world.addEntity(monst);
  std::vector<uint32_t> esqueleto = {1, 20, 1, 2500, 2700};
  std::stringstream bufferEnt;
  msgpack::pack(bufferEnt, esqueleto);
  sendMsg(bufferEnt.str());
  receiver.join();
  sender.join();
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
  std::vector<uint32_t> resp = {10, 0};
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
  return ss;
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
