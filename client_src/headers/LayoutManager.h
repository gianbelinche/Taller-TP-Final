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
    LayoutManager(const LayoutManager& copy) = delete;
    LayoutManager& operator=(const LayoutManager& copy) = delete;
    void decodeInventoryMessage(const std::vector<uint32_t> message);
    void decodeStateMessage(const std::vector<uint32_t> message);
    void decodeChatMessage(const std::vector<uint32_t> message);        

};

#endif