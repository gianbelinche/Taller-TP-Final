#ifndef CLASS_PERSISTOR
#define CLASS_PERSISTOR
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

class Persistor{
private:    
    std::fstream file;
    std::unordered_map<int,int> players;
public:
    Persistor();
    void persistPlayer(std::string file_name,std::vector<uint32_t> data,int player);
    std::vector<uint32_t> obtainPlayerData(std::string file_name,int player);
    void persistPasswordMap(std::string file_name,std::unordered_map<int,std::string> passwords);
    std::unordered_map<int,std::string> obtainPasswordMap(std::string file_name);
    ~Persistor();

};

#endif
