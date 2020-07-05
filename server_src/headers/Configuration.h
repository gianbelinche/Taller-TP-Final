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

 public:
  Configuration(std::string configFile);

  ~Configuration();

  /* Parsea el archivo de configuración */
  void parse(std::string configFile);

  void printConfig();

  const char* getPort();

  int getFPS();

  std::unordered_map<std::string, float>& getValues(std::string key);
};

#endif
