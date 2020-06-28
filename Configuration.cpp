#include "Configuration.h"

std::pair<std::vector<int>,std::vector<float>> Configuration::parse(std::string file_name,int int_number,int float_number){
    std::vector<int> data_int;
    std::vector<float> data_float;
    file.open(file_name,std::fstream::in);
    std::string line;
    int actual = 0;
    while (std::getline(file,line)){
        if (actual < int_number){
            data_int.push_back(stoi(line));
        } else {
            data_float.push_back(stof(line));
        }
        actual++;
    }
    file.close();
    return std::move(std::pair<std::vector<int>,std::vector<float>>(data_int,data_float));
}