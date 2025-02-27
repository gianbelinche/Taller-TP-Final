#include "../headers/Persistor.h"

#include <ios>
#include <iostream>
#include <msgpack.hpp>
#include <sstream>

#define DATA_SIZE 33
#define PLAYERS_MAP "config/players.cfg"
#define PLAYERS_DATA "config/usr.cfg"
#define PASSWORDS_FILE "config/pass.cfg"
#define BANKER_MAP "config/banker.cfg"

Persistor::Persistor() {
  file.open(PLAYERS_MAP);
  std::unordered_map<std::string, int> map;
  file.seekg(0, std::ios::end);
  int size = file.tellg();
  if (size > 0) {
    char* str = (char*)malloc(size);
    file.seekg(0);
    file.read(str, size);
    std::string string(str, size);
    msgpack::object_handle oh = msgpack::unpack(string.data(), size);
    msgpack::object deserialized = oh.get();
    deserialized.convert(map);
    this->players = std::move(map);
    free(str);
  }
  file.close();
  std::string pass_map_file = PASSWORDS_FILE;
  passwords = obtainPasswordMap(pass_map_file);
}

Persistor::~Persistor() {
  file.open(PLAYERS_MAP, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, players);
  buff.seekg(0);
  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

void Persistor::persistPasswordMap() {
  std::unique_lock<std::mutex> l(passMutex);

  file.open(PASSWORDS_FILE, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, passwords);
  buff.seekg(0);

  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

std::unordered_map<std::string, std::string> Persistor::obtainPasswordMap(
    std::string& file_name) {
  std::unique_lock<std::mutex> l(passMutex);
  file.open(file_name);
  std::unordered_map<std::string, std::string> passwords;
  file.seekg(0, std::ios::end);
  int size = file.tellg();
  if (size <= 0) {
    file.close();
    return passwords;
  }
  char* str = (char*)malloc(size);
  file.seekg(0);
  file.read(str, size);
  std::string string(str, size);
  msgpack::object_handle oh = msgpack::unpack(string.data(), size);
  msgpack::object deserialized = oh.get();
  deserialized.convert(passwords);
  free(str);
  file.close();
  return passwords;
}

void Persistor::persistPlayer(std::vector<uint32_t> data, std::string& player) {
  std::unique_lock<std::mutex> l(usersMutex);
  if (players.find(player) == players.end()) {
    file.open(PLAYERS_DATA, std::fstream::app);
    players[player] = file.tellg();
  } else {
    file.open(PLAYERS_DATA);
    file.seekg(players[player]);
  }
  for (int i = 0; i < DATA_SIZE; i++) {
    char* binary_data;
    uint32_t* data_ptr = &data[i];
    binary_data = (char*)data_ptr;
    file.write(binary_data, 4);
  }
  file.close();
}

std::vector<uint32_t> Persistor::obtainPlayerData(std::string& player) {
  std::vector<uint32_t> data;
  std::unique_lock<std::mutex> l(usersMutex);
  if (players.find(player) == players.end()) {
    // throw Exception , player not in file
    return data;
  }
  int offset = players[player];
  file.open(PLAYERS_DATA);
  file.seekg(offset);
  for (int i = 0; i < DATA_SIZE; i++) {
    char* binary_data = (char*)malloc(4);
    file.read(binary_data, 4);
    uint32_t* actual_data = (uint32_t*)binary_data;
    data.push_back(*actual_data);
    free(binary_data);
  }
  file.close();
  return data;
}

std::unordered_map<std::string, std::string>& Persistor::getPasswords() {
  return passwords;
}

void Persistor::persistUsrMap() {
  file.open(PLAYERS_MAP, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, players);
  buff.seekg(0);
  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

void Persistor::addPassword(std::string& user, std::string&& pass) {
  std::unique_lock<std::mutex> l(passMutex);
  passwords[user] = pass;
}

void Persistor::persistBank(
                  std::unordered_map<uint32_t,std::vector<uint32_t>> map){
  std::unique_lock<std::mutex> l(bankMutex);
  file.open(BANKER_MAP, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, map);
  buff.seekg(0);

  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

std::unordered_map<uint32_t,std::vector<uint32_t>> 
Persistor::obtainBank(){
  std::unique_lock<std::mutex> l(bankMutex);
  file.open(BANKER_MAP);
  std::unordered_map<uint32_t, std::vector<uint32_t>> bank;
  file.seekg(0, std::ios::end);
  int size = file.tellg();
  if (size <= 0) {
    file.close();
    return bank;
  }
  char* str = (char*)malloc(size);
  file.seekg(0);
  file.read(str, size);
  std::string string(str, size);
  msgpack::object_handle oh = msgpack::unpack(string.data(), size);
  msgpack::object deserialized = oh.get();
  deserialized.convert(bank);
  free(str);
  file.close();
  return bank;
}

