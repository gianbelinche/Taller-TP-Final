#include "ClientProtocol.h"

#define MOVE 0
#define CLICK_ENTITY 1
#define CLICK_INVENTORY 2

ClientProtocol::ClientProtocol() {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::makeMsgMove(uint32_t ID, uint32_t moveType, 
                                 std::vector<uint32_t> &msg) {
    msg.emplace_back(MOVE);
    msg.emplace_back(ID);
    msg.emplace_back(moveType);
}

void ClientProtocol::makeMsgClickEntity(uint32_t ID, std::vector<uint32_t> &msg) {
    msg.emplace_back(CLICK_ENTITY);
    msg.emplace_back(ID);
}

void ClientProtocol::makeMsgClickInventory(uint32_t ID, uint32_t slot, 
                                           std::vector<uint32_t> &msg) {
    msg.emplace_back(CLICK_INVENTORY);
    msg.emplace_back(ID);
    msg.emplace_back(slot);
}
