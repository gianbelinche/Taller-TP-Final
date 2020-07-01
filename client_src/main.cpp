#include "Persistor.h"
#include "Configuration.h"
#include <iostream>

int main(){
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
    /*
    Configuration config;
    std::pair<std::vector<int>,std::vector<float>> data = config.parse("config.txt",5,4);
    for (int i = 0; i < 5 ;i++){
        std::cout << (data.first)[i] << std::endl;
    }
    for (int i = 0; i < 4; i++){
        std::cout << (data.second)[i] << std::endl;
    }*/

    return 0;
}