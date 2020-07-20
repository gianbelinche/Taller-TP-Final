#ifndef CLASS_CONFIGURATION
#define CLASS_CONFIGURATION

#include <fstream>
#include <string>
#include <unordered_map>

class Configuration {
 private:
  std::fstream file;
  std::unordered_map<std::string, std::unordered_map<std::string, float>>
      configValues;
  std::unordered_map<int, std::string> itemToStr;
  std::unordered_map<int, char const*> typeToSpawn;
  const char* port_s;

 public:
  Configuration(std::string configFile);

  ~Configuration();

  /* Parsea el archivo de configuración */
  void parse(std::string& configFile);

  int getPort();

  int getFPS();

  float getConfigValue(std::string&& variable);

  std::unordered_map<std::string, float>& getValues(std::string&& key);

  std::unordered_map<std::string, float>& getValuesByItemType(int itemType);

  std::string& getItemName(int itemType);

  const char* spawnStrByMonsterType(int monsterType);

 private:
  void generateItemNames();
  
  void generateSpawnNames();
};

#endif
