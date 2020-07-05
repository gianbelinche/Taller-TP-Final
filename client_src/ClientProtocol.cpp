#include "ClientProtocol.h"
#define MOVE 0
#define CLICK_ENTITY 1
#define CLICK_INVENTORY 2
#define SEND_MESSAGE 3
#define LOGIN 4
#define CONNECTION 5
ClientProtocol::ClientProtocol() {}

ClientProtocol::~ClientProtocol() {}

std::vector<uint32_t> ClientProtocol::makeMsgMove(uint32_t ID, 
                                                  uint32_t moveType) {                                                
    std::vector<uint32_t> msg;
    msg.emplace_back(MOVE);
    msg.emplace_back(ID);
    msg.emplace_back(moveType);
    return msg;
}

std::vector<uint32_t> ClientProtocol::makeMsgClickEntity(uint32_t ID) {
    std::vector<uint32_t> msg;
    msg.emplace_back(CLICK_ENTITY);
    msg.emplace_back(ID);
    return msg;
}

std::vector<uint32_t> ClientProtocol::makeMsgClickInventory(uint32_t ID,
                                                            uint32_t slot) {
    std::vector<uint32_t> msg;
    msg.emplace_back(CLICK_INVENTORY);
    msg.emplace_back(ID);
    msg.emplace_back(slot);
    return msg;
}

std::vector<uint32_t> ClientProtocol::makeMsgSendCommand(uint32_t ID,
                                                         std::string command){
    std::vector<uint32_t> msg;
    msg.emplace_back(SEND_MESSAGE);
    msg.emplace_back(ID);
    for (unsigned int i = 0; i < command.size();i++){
        msg.emplace_back((uint32_t)command[i]);
    }
    return msg;
}

std::vector<uint32_t> ClientProtocol::makeMsgLogin(uint32_t ID,
                                                    std::string user,
                                                    std::string password){
    std::vector<uint32_t> msg;
    msg.emplace_back(LOGIN);
    msg.emplace_back(ID);
    msg.emplace_back(user.size());
    for (unsigned int i = 0; i < user.size();i++){
        msg.emplace_back((uint32_t)user[i]);
    }
    for (unsigned int i = 0; i < password.size();i++){
        msg.emplace_back((uint32_t)password[i]);
    }
    return msg;
}

std::vector<uint32_t> ClientProtocol::makeMsgConnection(uint32_t ID){
    std::vector<uint32_t> msg;
    msg.emplace_back(CONNECTION);
    msg.emplace_back(ID);
    return msg;
}