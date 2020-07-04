#include "Persistor.h"

#include <ios>
#include <iostream>
#include <msgpack.hpp>
#include <sstream>

#define DATA_SIZE 35
#define PLAYERS_MAP "players_map"

Persistor::Persistor() {
  file.open(PLAYERS_MAP);
  std::unordered_map<int, int> map;
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
}

Persistor::~Persistor() {
  file.open(PLAYERS_MAP, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, players);
  buff.seekg(0);
  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

void Persistor::persistPasswordMap(
    std::string file_name, std::unordered_map<int, std::string> passwords) {
  file.open(file_name, std::fstream::out | std::fstream::trunc);
  std::stringstream buff;
  msgpack::pack(buff, passwords);
  buff.seekg(0);
  file.write(&buff.str()[0], buff.str().size());
  file.close();
}

std::unordered_map<int, std::string> Persistor::obtainPasswordMap(
    std::string file_name) {
  file.open(file_name);
  std::unordered_map<int, std::string> passwords;
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

void Persistor::persistPlayer(std::string file_name, std::vector<uint32_t> data,
                              int player) {
  if (players.find(player) == players.end()) {
    file.open(file_name, std::fstream::app);
    players[player] = file.tellg();
  } else {
    file.open(file_name);
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

std::vector<uint32_t> Persistor::obtainPlayerData(std::string file_name,
                                                  int player) {
  std::vector<uint32_t> data;

  if (players.find(player) == players.end()) {
    // throw Exception , player not in file
    return data;
  }
  int offset = players[player];
  file.open(file_name);
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