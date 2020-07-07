#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Map {
 private:
  std::map<uint32_t, std::vector<std::string>> tiles;
  std::vector<std::vector<uint32_t>> terrain;
  std::vector<std::vector<uint32_t>> structures;
  std::vector<std::vector<bool>> collisions;
  std::vector<std::vector<bool>> cities;

 public:
  explicit Map(const char* mapPath);

  ~Map();

  std::vector<std::vector<bool>>& getCitiesMap();

  std::vector<std::vector<bool>>& getCollisionMap();

  std::vector<std::vector<uint32_t>>& getTerrainMap();

  std::vector<std::vector<uint32_t>>& getStructuresMap();

  std::map<uint32_t, std::vector<std::string>>& getTiles();
};

#endif  // MAP_H
