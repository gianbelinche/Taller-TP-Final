#ifndef CLASS_CONFIGURATION
#define CLASS_CONFIGURATION
#include <istream>
#include <vector>
#include <string>

class Configuration{
private:    
    std::ifstream file;
public:
    std::vector<uint32_t> parse(std::string file_name);    
};

#endif
