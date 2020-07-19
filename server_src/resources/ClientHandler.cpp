#include "../headers/ClientHandler.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <msgpack.hpp>
#include <sstream>
#include "../headers/PlayerNet.h"

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
  PlayerNet* player = nullptr;
  try {
    std::pair<std::string, std::vector<uint32_t>> playerDat =
      std::move(getCredentials());
    std::vector<uint32_t> playerInfo = playerDat.second;
  
    sendMap();

    ServerSender sender(peer, outgoingMessages);
    ServerReceiver receiver(peer, incomingMessages);
    outgoingMessages.disable();
    dispatcher.addPlayerQueue(playerInfo[0], &outgoingMessages);
    world.addPlayerFromData(playerInfo);
    world.addUsernameId(playerDat.first, playerInfo[0]);
    world.addIdUsername(playerInfo[0], playerDat.first);

    sender.start();
    receiver.start();

    sender.join();
    receiver.stop();
    receiver.join();

    player = world.getPlayer(playerInfo[0]);
    std::string username = world.getUsernameById(player->getId());
    persistor.persistPlayer(std::move(player->getData()),username);

    world.rmPlayer(playerInfo[0]);  // Id
    world.rmIdUsr(playerInfo[0]);
    world.rmUsrId(playerDat.first);

    outgoingMessages.close();
    listener.entityDisappear(playerInfo[0]);
    online = false;  
  }catch(SocketException& e){}
  if (player != nullptr) {
    delete player;
  }
}

bool ClientHandler::finished() { return !online; }

std::pair<std::string, std::vector<uint32_t>> ClientHandler::getCredentials() {
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

    if(len == 0){
      throw SocketException("Error al recibir");
    }

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

    if (world.isPlayerConnected(user_s)){
      sendFailedLogin();
      user_s.clear();
      pass_s.clear();
      continue;
    }

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

  persistor.persistUsrMap();

  std::stringstream pInfoBuff;
  msgpack::pack(pInfoBuff, sendablePlayInfo);
  std::string pInfoBuffStr = pInfoBuff.str();
  sendMsg(pInfoBuffStr);
  return std::make_pair(user_s, playerInfo);
}

void ClientHandler::sendMap() {
  sendTiles();
  sendTerrain();
  sendStructures();
}

void ClientHandler::sendMsg(std::string& msg) {
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
  std::string mapBufferStr = mapBuffer.str();
  sendMsg(mapBufferStr);
}

void ClientHandler::sendTerrain() {
  std::stringstream mapBuffer;
  std::vector<std::vector<uint32_t>>& terrain = map.getTerrainMap();
  msgpack::pack(mapBuffer, terrain);
  std::string mapBufferStr = mapBuffer.str();
  sendMsg(mapBufferStr);
}

void ClientHandler::sendStructures() {
  std::stringstream mapBuffer;
  std::vector<std::vector<uint32_t>>& structures = map.getStructuresMap();
  msgpack::pack(mapBuffer, structures);
  std::string mapBufferStr = mapBuffer.str();
  sendMsg(mapBufferStr);
}

void ClientHandler::sendSuccesfulLogin() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 1};
  msgpack::pack(loginBuffer, login);
  std::string loginBufferStr = loginBuffer.str();
  sendMsg(loginBufferStr);
}

void ClientHandler::sendFailedLogin() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 0};
  msgpack::pack(loginBuffer, login);
  std::string loginBufferStr = loginBuffer.str();
  sendMsg(loginBufferStr);
}

void ClientHandler::sendPlayerCreationNeeded() {
  std::stringstream loginBuffer;
  std::vector<uint32_t> login = {10, 2};
  msgpack::pack(loginBuffer, login);
  std::string loginBufferStr = loginBuffer.str();
  sendMsg(loginBufferStr);
}

void ClientHandler::setInitialState(std::vector<uint32_t>& playerInfo, 
                                    std::vector<uint32_t>& choices) {
  playerInfo.push_back(idGenerator++);                                // Id
  playerInfo.push_back(config.getValues("Player")["initialX"]);       // X
  playerInfo.push_back(config.getValues("Player")["initialY"]);       // Y
  playerInfo.push_back(config.getValues("Player")["initialLevel"]);   // Nivel
  playerInfo.push_back(config.getValues("Player")["initialExp"]);     // Exp
  playerInfo.push_back(choices[1]);                                   // Raza
  playerInfo.push_back(choices[2]);                                   // Clase
  playerInfo.push_back(config.getValues("Player")["initialGold"]);    // Oro
  playerInfo.push_back(config.getValues("Player")["initialState"]);   // Estado
}

void ClientHandler::setInitialInventory(std::vector<uint32_t>& playerInfo) {
  int initial_weapon = config.getValues("Player")["initialWeapon"];
  int initial_helmet = config.getValues("Player")["initialHelmet"];
  int initial_armor = config.getValues("Player")["initialArmor"];
  int initial_shield = config.getValues("Player")["initialShield"];
  playerInfo.push_back(initial_weapon);  // Arma
  playerInfo.push_back(initial_helmet);  // Casco
  playerInfo.push_back(initial_armor);   // Armadura
  playerInfo.push_back(initial_shield);  // Escudo

  int invItem = 0;
  
  if (initial_weapon != 0){
    playerInfo.push_back(initial_weapon); //Arma en el inventario
    invItem++;
  }
  if (initial_helmet != 0){
    playerInfo.push_back(initial_helmet); //Casco en el inventario
    invItem++;
  }
  if (initial_armor != 0){
    playerInfo.push_back(initial_armor);  //Armadura en el inventario
    invItem++;
  }
  if (initial_shield != 0){
    playerInfo.push_back(initial_shield); //Escudo en el inventario
    invItem++;
  }

  for (; invItem < INVENTORY_SIZE; invItem++) {
    playerInfo.push_back(0);
  }
}

void ClientHandler::handleNewPlayer(std::string& user) {
  std::string len_s = receiveMsg(sizeof(uint32_t));
  uint32_t len = *((uint32_t*)len_s.data());
  len = ntohl(len);

  if (len == 0){
    throw SocketException("Error al recibir");
  }

  std::string packInfo = receiveMsg(len);
  std::vector<uint32_t> choices;
  msgpack::object_handle oh = msgpack::unpack(packInfo.data(), packInfo.size());
  oh.get().convert(choices);

  std::vector<uint32_t> playerInfo;

  setInitialState(playerInfo, choices);
  setInitialInventory(playerInfo);

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