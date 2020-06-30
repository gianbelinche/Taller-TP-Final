#include "ClientHandler.h"


ClientHandler::ClientHandler(Socket p, Persistor& persist) 
    : peer(std::move(p)),
      persistor(persist) {}

ClientHandler::~ClientHandler() {
    
}
