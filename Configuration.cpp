#include "Configuration.h"

std::vector<uint32_t> Configuration::parse(std::string file_name){
    std::vector<uint32_t> data;
    file.open(file_name);
    std::string line;
    while (std::getline(file,line)){
        data.push_back(stoi(line));
    }
    file.close();
    return std::move(data);
}