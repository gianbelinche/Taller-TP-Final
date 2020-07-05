#include "../headers/Configuration.h"

#include "json/json.h"

#include <iostream>

Configuration::Configuration(std::string configFile) { parse(configFile); }

Configuration::~Configuration() {}

void Configuration::parse(std::string configFile) {
  file.open(configFile, std::fstream::in);
  Json::Value json_map;
  Json::Reader reader;
  reader.parse(file, json_map);

  for (Json::Value::const_iterator itr = json_map.begin();
       itr != json_map.end(); itr++) {
    Json::Value json_inside_map = *itr;
    std::unordered_map<std::string, float> real_inside_map;
    for (Json::Value::const_iterator internal_itr = json_inside_map.begin();
         internal_itr != json_inside_map.end(); internal_itr++) {
      real_inside_map[internal_itr.key().asString()] =
          (*internal_itr).asFloat();
    }
    configValues[itr.key().asString()] = std::move(real_inside_map);
  }
}

void Configuration::printConfig() {
  for (auto& k: configValues) {
    std::cout << k.first << std::endl;
    for (auto& kint: k.second) {
      std::cout << "Clav: " << kint.first << " Valor: " << kint.second << std::endl;
    }
  std::cout << "\n";
  }
}

const char* Configuration::getPort() {
  int port = configValues["config"]["port"];
  std::string port_s = std::to_string(port);
  return port_s.data();
}

int Configuration::getFPS() {
  return (int)configValues["config"]["FPS"];
}

std::unordered_map<std::string, float>& Configuration::getValues(std::string key) {
  return configValues[key];
}

