#include "Server.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "resources/Map.h"


Server::Server(const char* port, Configuration configuration)
    : port(port), config(std::move(configuration)) {}

Server::~Server() {}

void Server::run() {
  Map map(MAP_PATH);
  
}
