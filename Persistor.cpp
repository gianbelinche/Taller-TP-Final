#include "Persistor.h"
#define DATA_SIZE 35
#include <iostream>
#include <ios>

Persistor::Persistor() : total(0){}

void Persistor::persistPlayer(std::string file_name,std::vector<uint32_t> data,int player){
    if (players.find(player) == players.end()){
        file.open(file_name,std::fstream::app);
        players[player] = file.tellg();
    } else {
        file.open(file_name);
        file.seekg(players[player]);
    }
    for (int i = 0; i < DATA_SIZE;i++){
        char* binary_data;
        uint32_t* data_ptr = &data[i];
        binary_data = (char*) data_ptr;
        file.write(binary_data,4);
    }
    file.close();
}

std::vector<uint32_t> Persistor::obtainPlayerData(std::string file_name,int player){
    std::vector<uint32_t> data;
    
    if (players.find(player) == players.end()){
        //throw Exception , player not in file
        return data;
    }
    int offset = players[player];
    file.open(file_name);
    file.seekg(offset);
    for (int i = 0; i < DATA_SIZE; i++){
        char* binary_data = (char*) malloc(4);
        file.read(binary_data,4);
        uint32_t* actual_data = (uint32_t*) binary_data;
        data.push_back(*actual_data);
        free(binary_data);
    }
    file.close();
    return std::move(data);
}