#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include <vector>
#include <stdint.h>
#include <string>

class ClientProtocol {
    public:
        ClientProtocol();
        ~ClientProtocol();

        ClientProtocol(const ClientProtocol &copy) = delete;

        std::vector<uint32_t> makeMsgMove(uint32_t ID, uint32_t moveType);
        std::vector<uint32_t> makeMsgClickEntity(uint32_t ID);
        std::vector<uint32_t> makeMsgClickInventory(uint32_t ID,
                                                    uint32_t slot);
        std::vector<uint32_t> makeMsgSendCommand(uint32_t ID,
                                                 std::string command);
        std::vector<uint32_t> makeMsgLogin(uint32_t ID,std::string user,
                                           std::string password);                                   
};

#endif
