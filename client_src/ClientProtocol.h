#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include <vector>
#include <stdint.h>

class ClientProtocol {
    public:
        ClientProtocol();
        ~ClientProtocol();
        void makeMsgMove(uint32_t ID, uint32_t moveType, 
        
                         std::vector<uint32_t> &msg);
        void makeMsgClickEntity(uint32_t ID, std::vector<uint32_t> &msg);
        void makeMsgClickInventory(uint32_t ID, uint32_t slot, 
                                   std::vector<uint32_t> &msg);
};

#endif
