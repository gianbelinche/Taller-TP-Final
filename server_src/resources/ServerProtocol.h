#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <string>

class ServerProtocol {
private:
  
public:
  ServerProtocol();
  
  ~ServerProtocol();

  void decode(std::string packedEvent);
};

#endif // SERVERPROTOCOL_H
