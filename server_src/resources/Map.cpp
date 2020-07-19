#include "../headers/Map.h"

#include <fstream>
#include <iostream>
#include <utility>

void Map::initLayers(Json::Value& mapValues) {
  const Json::Value& layers = mapValues["layers"];  // Array de capas

  if (!layers) {
    throw Json::Exception("Error: no se encontró layers.");
  }

  for (int lay = 0; lay < 4; lay++) {
    const Json::Value& layer = layers[lay]["data"]; // Array de enteros de capa i
    const Json::Value& width = layers[lay]["width"]; // Ancho de la capa i
    const Json::Value& height = layers[lay]["height"]; // Alto de la capa i

    if (!(layer && height && width)) {
      throw Json::Exception("Error: no se encontró data de capa.");
    }

    uint32_t cont = 0;

    if (lay == 0 || lay == 1) {
      for (Json::Value::UInt r = 0; r < height.asUInt(); r++) {
        std::vector<uint32_t> row;
        for (Json::Value::UInt c = 0; c < width.asUInt(); c++) {
          row.emplace_back(layer[cont].asUInt());
          cont++;
        }
        switch (lay) {
          case 0:
            terrain.emplace_back(row);
            break;
          
          case 1:
            structures.emplace_back(row);
            break;

          default:
            break;
        }
      }
    } else {
      for (Json::Value::UInt r = 0; r < height.asUInt(); r++) {
        std::vector<bool> row;
        for (Json::Value::UInt c = 0; c < width.asUInt(); c++) {
          row.emplace_back(layer[cont].asUInt());
          cont++;
        }
        switch (lay) {
          case 2:
            collisions.emplace_back(row);
            break;

          case 3:
            cities.emplace_back(row);
            break;

          default:
            break;
        }
      }
    }
  }
}

void Map::initTiles(Json::Reader& mapReader, Json::Value& mapValues) {
  /*
   * Creo el hash que contiene como:
   *  -clave: al numero asignado al tileset.
   *  -valor: un vector de valores importantes en forma de strings.
  */

  const Json::Value& tilesets = mapValues["tilesets"];  // Array de tilesets

  if (!tilesets) {
    throw Json::Exception("Error: no se encontró array de tilesets");
  }

  for (Json::Value::ArrayIndex i = 0; i < tilesets.size(); i++) {
    std::ifstream ifsl(tilesets[i]["source"].asString());
    Json::Value vall;
    mapReader.parse(ifsl, vall);

    uint32_t key = tilesets[i]["firstgid"].asUInt();
    std::vector<std::string> vt;

    vt.emplace_back(vall["image"].asString());
    vt.emplace_back(vall["tileheight"].asString());
    vt.emplace_back(vall["tilewidth"].asString());

    tiles[key] = vt;
  }
}

Map::Map(const char* mapPath) {
  std::ifstream mapFile(mapPath);
  Json::Reader mapReader;
  Json::Value mapValues;
  mapReader.parse(mapFile, mapValues);

  initLayers(mapValues);
  initTiles(mapReader, mapValues);
}

Map::~Map() {}

std::vector<std::vector<bool>>& Map::getCitiesMap() { return cities; }

std::vector<std::vector<bool>>& Map::getCollisionMap() { return collisions; }

std::vector<std::vector<uint32_t>>& Map::getTerrainMap() { return terrain; }

std::vector<std::vector<uint32_t>>& Map::getStructuresMap() {
  return structures;
}

std::map<uint32_t, std::vector<std::string>>& Map::getTiles() { return tiles; }
