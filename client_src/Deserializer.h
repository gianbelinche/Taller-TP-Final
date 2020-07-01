#ifndef CLASS_DESERIALIZER
#define CLASS_DESERIALIZER
#include "Layout.h"
#include "GraphicInventory.h"
#include "MiniChat.h"
#include "ExpBar.h"
#include <vector>

class Deserializer{
private:
    Layout& layout;
    GraphicInventory& inventory;
    MiniChat& chat;
    ExpBar expbar;

public:
    Deserializer(Layout& layout,GraphicInventory& inventory,MiniChat& chat,ExpBar expbar);

    void decodeInventoryMessage(std::vector<uint32_t> message);
    void decodeStateMessage(std::vector<uint32_t> message);
    void decodeChatMessage(std::vector<uint32_t> message);        

};

#endif