//#include "Persistor.h"
//#include "Configuration.h"
#include "Serializer.h"
#include <iostream>
#include <sstream>

int main(){
    /*
    Persistor persistor;
    std::vector<uint32_t> data;
    for (uint32_t i = 0; i < 35; i++){
        data.push_back(i);
    }
    //persistor.persistPlayer("persistencia",data,1);
    data.clear();
    for (uint32_t i = 0; i < 35; i++){
        data.push_back(i * 2);
    }
    //persistor.persistPlayer("persistencia",data,2);
    //persistor.persistPlayer("persistencia",data,335);
    std::vector<uint32_t> recv_data = persistor.obtainPlayerData("persistencia",335);
    
    for (int i = 0; i < 35 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    recv_data = persistor.obtainPlayerData("persistencia",2);
    for (int i = 0; i < 35 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    
    Configuration config;
    std::pair<std::vector<int>,std::vector<float>> data = config.parse("config.txt",5,4);
    for (int i = 0; i < 5 ;i++){
        std::cout << (data.first)[i] << std::endl;
    }
    for (int i = 0; i < 4; i++){
        std::cout << (data.second)[i] << std::endl;
    }*/

    Serializer ser;
    std::vector<uint32_t> message = ser.serializeCommand(20,"Esto es un comanod");
    std::stringstream recvd_message;

    for (unsigned int i = 2; i < message.size(); i++){
        recvd_message << (char) message[i];
    }
    std::cout << recvd_message.str() << std::endl;

    return 0;
}