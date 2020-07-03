#ifndef CLASS_PERSISTOR
#define CLASS_PERSISTOR

#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

class Persistor {
 private:
  std::fstream file;
  std::unordered_map<int, int> players;

 public:
  Persistor();

  ~Persistor();

  void persistPlayer(std::string file_name, std::vector<uint32_t> data,
                     int player);

  std::vector<uint32_t> obtainPlayerData(std::string file_name, int player);

  std::unordered_map<int, int>& getPlayersMap();
};

#endif
