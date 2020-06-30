#include "ClientHandler.h"

ClientHandler::ClientHandler(Socket p, Persistor& persist)
    : peer(std::move(p)), persistor(persist) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {}

bool ClientHandler::finished() { return online; }
