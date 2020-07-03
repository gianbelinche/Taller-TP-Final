#include <string>
#include <unordered_map>

class Configuration {
 private:
  std::unordered_map<std::string, std::unordered_map<std::string, float>>
      config;

 public:
  explicit Configuration(const char* config_path);

  ~Configuration();

  const char* getPort();
};
