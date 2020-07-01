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
    //Persiste los datos de player en un archivo binario, manteniendo 
    //Una referencia a donde fueron persistidos
    void persistPlayer(std::string file_name,std::vector<uint32_t> data,int player);
    //Obtiene los datos persistidos de player
    std::vector<uint32_t> obtainPlayerData(std::string file_name,int player);
    //Persiste el mapa de contraseñas de los jugadores
    void persistPasswordMap(std::string file_name,std::unordered_map<int,std::string> passwords);
    //Obtiene los datos de las contraseñas de los jugadores
    std::unordered_map<int,std::string> obtainPasswordMap(std::string file_name);
    ~Persistor();

};

#endif
