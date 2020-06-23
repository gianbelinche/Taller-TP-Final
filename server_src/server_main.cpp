#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common_client_handler.h"
#include "common_SocketExcept.h"
#include "server_acceptor.h"

enum exit_codes{SUCCESS, ERROR};

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Cantidad de argumentos incorrecta" << std::endl;
    return ERROR;
  }
  std::vector<int> numbers;
  std::ifstream num_file(argv[2]);
  if (num_file.is_open()) {
    for (std::string line; std::getline(num_file, line); ) {
      numbers.push_back(std::stoi(line));
    }
  } else {
    std::cerr << "Error al abrir el archivo " << argv[2] << std::endl;
  }

  Acceptor client_acceptor(argv[1], numbers);
  try {
    client_acceptor.start();
  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
    return ERROR;
  }

  std::string usr_input = "";
  while (usr_input != "q") {
    std::cin >> usr_input;
  }
  client_acceptor.stop_accepting();
  return 0;
}
