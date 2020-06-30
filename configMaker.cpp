#include "json/json.h"
#include <fstream>

int main(){
    Json::Value inside_map;
    inside_map["velocidad"] = 0.025;
    inside_map["vida"] = 0.248;
    inside_map["mana"] = 53.23;
    /* completar con lo que haga falta */
    Json::Value outside_map;
    outside_map["mapa1"] = inside_map;
    Json::Value inside_map2;
    inside_map2["velocidad"] = 18.5;
    inside_map2["vida"] = 98.6;
    inside_map2["mana"] = 74.6;
    outside_map["mapa2"] = inside_map2;

    Json::StreamWriterBuilder writer;
    std::string str = writer.write(outside_map);
    std::fstream file("config.json");
    file.write(&str[0],str.size());
}