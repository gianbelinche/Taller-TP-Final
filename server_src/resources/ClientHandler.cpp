#include "../headers/ClientHandler.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <msgpack.hpp>
#include <sstream>

#define INVENTORY_SIZE 20

ClientHandler::ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                             std::atomic<uint32_t>& idAssigner,
                             ProtectedQueue<std::string>& incoming,
                             MessageDispatcher& msgDispatcher, GameState& state,
                             ServerEventListener& eventListener,
                             Configuration& config)
    : peer(std::move(p)),
      persistor(persist),
      online(true),
      map(worldMap),
      idGenerator(idAssigner),
      incomingMessages(incoming),
      dispatcher(msgDispatcher),
      world(state),
      listener(eventListener),
      config(config) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::vector<uint32_t> playerInfo = std::move(getCredentials());
  sendMap();

  ServerSender sender(peer, outgoingMessages);
  ServerReceiver receiver(peer, incomingMessages);
  outgoingMessages.disable();
  dispatcher.addPlayerQueue(playerInfo[0], &outgoingMessages);
  world.addPlayerFromData(playerInfo);

  sender.start();
  receiver.start();
  /* --- HARDCODEO --- */

  /*Class* cl1 = new Class(0, 1, 2, 3);
  Race* r1 = new Race(0, 100, 1, 2);
  PlayerNet* player1 =
      new PlayerNet(2500, 2500, 1550, world, 100, 50, 6, 200, 2, 90, nullptr,
                    nullptr, nullptr, nullptr, &PlayerState::normal, cl1, r1);

  world.addPlayer(player1);

  usleep(10000000);
  MonsterType* mt = new MonsterType(20, 10);
  Monster* monst = mt->newMonster(20, 2500, 2700, 1, world, listener);
  world.addEntity(monst);
  std::vector<uint32_t> esqueleto = {1, 20, 1, 2500, 2700};
  std::stringstream bufferEnt;
  msgpack::pack(bufferEnt, esqueleto);
  sendMsg(bufferEnt.str());*/
  receiver.join();
  sender.join();
}

bool ClientHandler::finished() { return !online; }

std::vector<uint32_t> ClientHandler::getCredentials() {
  std::string user_s;
  std::string pass_s;
  std::unordered_map<std::string, std::string>& passwords =
      persistor.getPasswords();
  bool correctCredentials = false;
  bool creationNeeded = false;

  while (!correctCredentials) {
    std::string len_s = receiveMsg(sizeof(uint32_t));
    uint32_t len = *((uint32_t*)len_s.data());
    len = ntohl(len);

    std::string packedCred = receiveMsg(len);

    std::vector<uint32_t> credentials;
    msgpack::object_handle oh =
        msgpack::unpack(packedCred.data(), packedCred.size());
    oh.get().convert(credentials);

    uint32_t usrSize = credentials[1];
    std::vector<char> user(usrSize);
    for (uint32_t i = 0; i < usrSize; i++) {
      user[i] = credentials[i + 2];
    }
    std::vector<char> password(credentials.size() - usrSize - 2);
    for (size_t j = (2 + usrSize); j < credentials.size(); j++) {
      password[j - 2 - usrSize] = credentials[j];
    }
    user_s.append(user.data(), user.size());
    pass_s.append(password.data(), password.size());

    std::cout << "User:" << user_s << std::endl;
    std::cout << "Pass:" << pass_s << std::endl;

    if (passwords.find(user_s) != passwords.end()) {
      if (passwords[user_s] == pass_s) {  // Aplicar SHA
        sendSuccesfulLogin();
        correctCredentials = true;
      } else {
        sendFailedLogin();
        user_s.clear();
        pass_s.clear();
        continue;
      }
    } else {
      sendPlayerCreationNeeded();
      correctCredentials = true;
      creationNeeded = true;
    }
  }

  if (creationNeeded) {
    handleNewPlayer(user_s);
    persistor.addPassword(user_s, pass_s);
    // passwords[user_s] = pass_s;  // Aplicar sha
    persistor.persistPasswordMap();
  }
  std::vector<uint32_t> playerInfo = persistor.obtainPlayerData(user_s);
  std::vector<uint32_t> sendablePlayInfo =
      std::move(getSendablePlayerInfo(playerInfo));

  std::cout << "La info: \n";
  for (auto& elem : playerInfo) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
  persistor.persistUsrMap();

  std::stringstream pInfoBuff;
  msgpack::pack(pInfoBuff, sendablePlayInfo);
  sendMsg(pInfoBuff.str());
  return playerInfo;
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

void ClientHandler::sendSuccesfulLogin() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 1};
  msgpack::pack(loginBuffer, login);
  sendMsg(loginBuffer.str());
}

void ClientHandler::sendFailedLogin() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 0};
  msgpack::pack(loginBuffer, login);
  sendMsg(loginBuffer.str());
}

void ClientHandler::sendPlayerCreationNeeded() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 2};
  msgpack::pack(loginBuffer, login);
  sendMsg(loginBuffer.str());
}

void ClientHandler::handleNewPlayer(std::string user) {
  std::string len_s = receiveMsg(sizeof(uint32_t));
  uint32_t len = *((uint32_t*)len_s.data());
  len = ntohl(len);

  std::string packInfo = receiveMsg(len);
  std::vector<uint32_t> choices;
  msgpack::object_handle oh = msgpack::unpack(packInfo.data(), packInfo.size());
  oh.get().convert(choices);

  std::vector<uint32_t> playerInfo;

  playerInfo.push_back(idGenerator++);                                // Id
  playerInfo.push_back(config.getValues("Player")["initialX"]);       // X
  playerInfo.push_back(config.getValues("Player")["initialY"]);       // Y
  playerInfo.push_back(config.getValues("Player")["initialLevel"]);   // Nivel
  playerInfo.push_back(config.getValues("Player")["initialExp"]);     // Exp
  playerInfo.push_back(choices[1]);                                   // Raza
  playerInfo.push_back(choices[2]);                                   // Clase
  playerInfo.push_back(config.getValues("Player")["initialGold"]);    // Oro
  playerInfo.push_back(config.getValues("Player")["initialState"]);   // Estado
  playerInfo.push_back(config.getValues("Player")["initialWeapon"]);  // Arma
  playerInfo.push_back(config.getValues("Player")["initialHelmet"]);  // Casco
  playerInfo.push_back(config.getValues("Player")["initialArmor"]);  // Armadura
  playerInfo.push_back(config.getValues("Player")["initialShield"]);  // Escudo

  for (int i = 0; i < INVENTORY_SIZE; i++) {
    playerInfo.push_back(0);
  }

  persistor.persistPlayer(playerInfo, user);
}

std::vector<uint32_t> ClientHandler::getSendablePlayerInfo(
    std::vector<uint32_t>& playerData) {
  std::vector<uint32_t> sendable = {2};
  sendable.push_back(playerData[0]);   // Id
  sendable.push_back(playerData[5]);   // Raza
  sendable.push_back(playerData[1]);   // X
  sendable.push_back(playerData[2]);   // Y
  sendable.push_back(playerData[8]);   // Estado
  sendable.push_back(playerData[9]);   // Arma
  sendable.push_back(playerData[11]);  // Armadura
  sendable.push_back(playerData[12]);  // Escudo
  sendable.push_back(playerData[10]);  // Casco

  return sendable;
}