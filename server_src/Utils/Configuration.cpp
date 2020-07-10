#include "../headers/Configuration.h"

#include <iostream>

#include "../json/json.h"

Configuration::Configuration(std::string configFile) {
  parse(configFile);
  // Comienza el hardcodeo cosmico
  itemToStr[0] = "Sin equipamiento";
  itemToStr[1] = "Espada";
  itemToStr[2] = "Hacha";
  itemToStr[3] = "Martillo";
  itemToStr[4] = "Vara de Fresno";
  itemToStr[5] = "Flauta Elfica";
  itemToStr[6] = "Baculo Nudoso";
  itemToStr[7] = "Baculo Engarzado";
  itemToStr[8] = "Arco Simple";
  itemToStr[9] = "Arco Compuesto";
  itemToStr[10] = "Armadura de Cuero";
  itemToStr[11] = "Armadura de Placas";
  itemToStr[12] = "Tunica Azul";
  itemToStr[13] = "Capucha";
  itemToStr[14] = "Casco de Hierro";
  itemToStr[15] = "Escudo Tortuga";
  itemToStr[16] = "Escudo de Hierro";
  itemToStr[17] = "Sombrero Magico";
  itemToStr[18] = "Pocion de mana";
  itemToStr[19] = "Pocion de vida";
  itemToStr[20] = "Oro";
}

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
  for (auto& k : configValues) {
    std::cout << k.first << std::endl;
    for (auto& kint : k.second) {
      std::cout << "Clav: " << kint.first << " Valor: " << kint.second
                << std::endl;
    }
    std::cout << "\n";
  }
}

const char* Configuration::getPort() {
  int port = configValues["config"]["port"];
  std::string port_s = std::to_string(port);
  return port_s.data();
}

int Configuration::getFPS() { return (int)configValues["config"]["FPS"]; }

float Configuration::getConfigValue(std::string variable) {
  return configValues["config"][variable];
}

std::unordered_map<std::string, float>& Configuration::getValues(
    std::string key) {
  return configValues[key];
}

std::unordered_map<std::string, float>& Configuration::getValuesByItemType(
    int itemType) {
  return configValues[itemToStr[itemType]];
}

std::string Configuration::getItemName(int itemType) {
  return itemToStr[itemType];
}

