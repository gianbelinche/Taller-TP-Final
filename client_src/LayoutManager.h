#ifndef CLASS_LAYOUT_MANAGER
#define CLASS_LAYOUT_MANAGER
#include "Layout.h"
#include "GraphicInventory.h"
#include "MiniChat.h"
#include "ExpBar.h"
#include <vector>

class LayoutManager{
private:
    Layout& layout;
    GraphicInventory& inventory;
    MiniChat& chat;
    ExpBar& expbar;

public:
    LayoutManager(Layout& layout,GraphicInventory& inventory,MiniChat& chat,ExpBar& expbar);

    void decodeInventoryMessage(std::vector<uint32_t> message);
    void decodeStateMessage(std::vector<uint32_t> message);
    void decodeChatMessage(std::vector<uint32_t> message);        

};

#endif