#include "Map.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "../../JsonError.h"
#include "../../json/json.h"

Map::Map(const char* mapPath) {
  std::ifstream mapFile(mapPath);
  Json::Reader mapReader;
  Json::Value mapValues;
  mapReader.parse(mapFile, mapValues);

  /*
   * Busco el array de capas. El mapa se separa en "capas" que permiten
   * la superposición de elementos. Nuestro mapa se divide en dos capas
   * para poder poner edificaciones, arboles, etc.
   */
  const Json::Value& layers = mapValues["layers"];  // Array de capas

  /*
   * Si algo que se buscó en el .json no se encontró se setea el
   * const Json::Value&
   * en null.
   */
  if (!layers) {
    // throw JsonError("Error: no se encontró layers. JsonError: %s",
    // jsonerror);
  }

  /*
   * Ancho, alto y la data de cada capa.
   */
  const Json::Value& layer0 = layers[0]["data"];   // Array de enteros de capa 0
  const Json::Value& width0 = layers[0]["width"];  // Ancho de la capa 0
  const Json::Value& height0 = layers[0]["height"];  // Alto de la capa 0

  if (!(layer0 && height0 && width0)) {
    /* Buscar cómo obtener el error que genera jsoncpp */
    // throw JsonError("Error: no se encontró data de capa 0. JsonError: %s",
    // jsonerror);
  }

  const Json::Value& layer1 = layers[1]["data"];   // Array de enteros de capa 1
  const Json::Value& width1 = layers[1]["width"];  // Ancho de la capa 1
  const Json::Value& height1 = layers[1]["height"];  // Alto de la capa 1

  if (!(layer1 && height1 && width1)) {
    /* Buscar cómo obtener el error que genera jsoncpp */
    // throw JsonError("Error: no se encontró data de capa 1. JsonError: %s",
    // jsonerror);
  }

  const Json::Value& layer2 = layers[2]["data"];   // Array de enteros de capa 2
  const Json::Value& width2 = layers[2]["width"];  // Ancho de la capa 2
  const Json::Value& height2 = layers[2]["height"];  // Alto de la capa 2

  if (!(layer2 && height2 && width2)) {
    /* Buscar cómo obtener el error que genera jsoncpp */
    // throw JsonError("Error: no se encontró data de capa 1. JsonError: %s",
    // jsonerror);
  }

  /*
   * Creo las matrices que tienen la data de las capas.
   * Estas matrices se deben guardar para enviar a los clientes
   * Además, se deben guardar los valores:
   * height0, width0, height1 y width1 (no es necesario creo)
   */

  uint32_t cont = 0;

  /* Matriz de capa 0 */

  for (Json::Value::UInt i = 0; i < height0.asUInt(); i++) {
    std::vector<uint32_t> row;
    for (Json::Value::UInt j = 0; j < width0.asUInt(); j++) {
      row.emplace_back(layer0[cont].asUInt());
      cont++;
    }
    terrain.emplace_back(row);
  }

  /* Matriz de capa 1 */

  cont = 0;
  for (Json::Value::UInt i = 0; i < height1.asUInt(); i++) {
    std::vector<uint32_t> row;
    for (Json::Value::UInt j = 0; j < width1.asUInt(); j++) {
      row.emplace_back(layer1[cont].asUInt());
      cont++;
    }
    structures.emplace_back(row);
  }

  /* Matriz de capa de bloqueo */

  cont = 0;
  for (Json::Value::UInt i = 0; i < height2.asUInt(); i++) {
    std::vector<bool> row;
    for (Json::Value::UInt j = 0; j < width2.asUInt(); j++) {
      row.emplace_back(layer2[cont].asUInt());
      cont++;
    }
    collisions.emplace_back(row);
  }

  /*
   * Creo el hash que contiene como:
   *  -clave: al numero asignado al tileset.
   *  -valor: un vector de valores importantes en forma de strings.
   */

  const Json::Value& tilesets = mapValues["tilesets"];  // Array de tilesets

  for (Json::Value::ArrayIndex i = 0; i < tilesets.size(); i++) {
    std::ifstream ifsl(tilesets[i]["source"].asString());
    Json::Value vall;
    mapReader.parse(ifsl, vall);

    uint32_t key = tilesets[i]["firstgid"].asUInt();
    std::vector<std::string> v;

    v.emplace_back(vall["image"].asString());
    v.emplace_back(vall["tileheight"].asString());
    v.emplace_back(vall["tilewidth"].asString());

    tiles[key] = v;
  }
}

Map::~Map() {}

std::vector<std::vector<bool>>& Map::getCollisionMap() { return collisions; }

std::vector<std::vector<uint32_t>>& Map::getTerrainMap() { return terrain; }

std::vector<std::vector<uint32_t>>& Map::getStructuresMap() {
  return structures;
}

std::map<uint32_t, std::vector<std::string>>& Map::getTiles() { return tiles; }
