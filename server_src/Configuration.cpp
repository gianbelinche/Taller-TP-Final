#include "Configuration.h"
#include "json/json.h"

std::unordered_map<std::string,std::unordered_map<std::string,float>> 
Configuration::parse(std::string file_name){
    file.open(file_name,std::fstream::in);
    Json::Value json_map;
    Json::Reader reader;
    reader.parse(file,json_map);
    std::unordered_map<std::string,std::unordered_map<std::string,float>> real_map;

    for(Json::Value::const_iterator itr = json_map.begin();itr != json_map.end();itr++){
        Json::Value json_inside_map = *itr;
        std::unordered_map<std::string,float> real_inside_map;
        for (Json::Value::const_iterator internal_itr = json_inside_map.begin(); internal_itr != json_inside_map.end();internal_itr++){
            real_inside_map[internal_itr.key().asString()] = (*internal_itr).asFloat();
        }
        real_map[itr.key().asString()] = std::move(real_inside_map);
    }

    return std::move(real_map);
}
