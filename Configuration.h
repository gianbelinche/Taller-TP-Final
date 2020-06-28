#ifndef CLASS_CONFIGURATION
#define CLASS_CONFIGURATION
#include <fstream>
#include <vector>
#include <string>

class Configuration{
private:    
    std::fstream file;
public:
    std::pair<std::vector<int>,std::vector<float>> parse(std::string file_name,int int_number,int float_number);    
};

#endif
