#ifndef CLASS_SERIALIZER
#define CLASS_SERIALIZER
#include <vector>
#include <string>

class Serializer{
public:
    std::vector<uint32_t> serializeInventoryClick(int player_id,int slot);
    std::vector<uint32_t> serializeCommand(int player_id,std::string command);
};

#endif
