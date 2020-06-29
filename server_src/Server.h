#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <unordered_map>

#include "config/Configuration.h"
#include "resources/Thread.h"

#define MAP_PATH "../map.json"

class Server : public Thread {
 private:
  const char* port;
  Configuration config;
  
 public:
  Server(const char* port, Configuration configuration);

  ~Server();

  void run() override;

  void loadMap(const char* mapPath);
};

#endif // SERVER_H
