#include "Persistor.h"
#include "Configuration.h"
#include <iostream>

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
    std::vector<uint32_t> recv_data = persistor.obtainPlayerData("persistencia",1);
    
    for (int i = 0; i < 35 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    recv_data = persistor.obtainPlayerData("persistencia",2);
    for (int i = 0; i < 35 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    std::unordered_map<int,std::string> passwords = persistor.obtainPasswordMap("passwords.json");
    persistor.persistPasswordMap("passwords.json",passwords);
    }*/
    
    Configuration config;
    std::unordered_map<std::string,std::unordered_map<std::string,float>> data = config.parse("config.json");
    std::cout << data["config"]["fps"] << std::endl;
    std::cout << data["config"]["framesEntreSpawns"] << std::endl;
    std::cout << data["elfo"]["hpFactor"] << std::endl;
    std::cout << data["elfo"]["constitution"] << std::endl;
    std::cout << data["elfo"]["intelligence"] << std::endl;
    std::cout << data["enano"]["manaFactor"] << std::endl;
    std::cout << data["enano"]["strength"] << std::endl;


    return 0;
}