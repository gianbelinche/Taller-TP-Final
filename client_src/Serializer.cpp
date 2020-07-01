#include "Serializer.h"

std::vector<uint32_t> Serializer::serializeInventoryClick(int player_id,int slot){
    std::vector<uint32_t> data;
    data.push_back(2);
    data.push_back(player_id);
    data.push_back(slot);
    return std::move(data);
}

std::vector<uint32_t> Serializer::serializeCommand(int player_id,std::string command){
    std::vector<uint32_t> data;
    data.push_back(3);
    data.push_back(player_id);
    /* for para convertir string en ints */
    for (unsigned int i = 0; i < command.size();i++){
        data.push_back((uint32_t)command[i]);
    }
    return std::move(data);
}