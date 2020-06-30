#ifndef CLASS_CONFIGURATION
#define CLASS_CONFIGURATION
#include <fstream>
#include <unordered_map>
#include <string>

class Configuration{
private:    
    std::fstream file;
public:
    std::unordered_map<std::string,std::unordered_map<std::string,float>> 
    parse(std::string file_name);    
};

#endif
