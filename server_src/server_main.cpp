#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "headers/Configuration.h"
#include "headers/Server.h"
#include "headers/SocketException.h"

enum exit_codes{SUCCESS, ERROR};

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "Cantidad de argumentos incorrecta" << std::endl;
    return ERROR;
  }
  Configuration config(std::move(argv[1]));
  Server server(config.getPort(), config);

  try {
    server.start();
  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
    return ERROR;
  }

  std::string usr_input = "";
  while (usr_input != "q") {
    std::cin >> usr_input;
  }
  server.stop();
  server.join();
  return 0;
}
