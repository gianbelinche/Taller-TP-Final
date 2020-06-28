#include "Persistor.h"
#include <iostream>

int main(){
    Persistor persistor;
    std::vector<uint32_t> data;
    for (uint32_t i = 0; i < 35; i++){
        data.push_back(i);
    }
    persistor.persistPlayer("persistencia",data,1);
    data.clear();
    for (uint32_t i = 0; i < 10; i++){
        data.push_back(i * 2);
    }
    persistor.persistPlayer("persistencia",data,2);
    std::vector<uint32_t> recv_data = persistor.obtainPlayerData("persistencia",1);
    
    for (int i = 0; i < 35 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    recv_data = persistor.obtainPlayerData("persistencia",2);
    for (int i = 0; i < 10 ;i++){
        std::cout << recv_data[i] << std::endl;
    }
    return 0;
}