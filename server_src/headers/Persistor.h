#ifndef CLASS_PERSISTOR
#define CLASS_PERSISTOR
#include <fstream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class Persistor {
 private:
  std::fstream file;
  std::unordered_map<std::string, int> players;
  std::unordered_map<std::string, std::string> passwords;
  std::mutex usersMutex;
  std::mutex passMutex;

 public:
  Persistor();
  // Persiste los datos de player en un archivo binario, manteniendo
  // Una referencia a donde fueron persistidos
  void persistPlayer(std::vector<uint32_t> data, std::string player);

  // Obtiene los datos persistidos de player
  std::vector<uint32_t> obtainPlayerData(std::string player);

  // Persiste el mapa de contraseñas de los jugadores
  void persistPasswordMap();
                          
  // Obtiene los datos de las contraseñas de los jugadores
  std::unordered_map<std::string, std::string> obtainPasswordMap(std::string file_name);

  std::unordered_map<std::string, std::string>& getPasswords();

  void addPassword(std::string user, std::string pass);

  void persistUsrMap();

  ~Persistor();
};

#endif
