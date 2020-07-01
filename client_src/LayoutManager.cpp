#include "LayoutManager.h"
#include <sstream>

LayoutManager::LayoutManager(Layout& layout,GraphicInventory& inventory,MiniChat& chat,ExpBar& expbar) : layout(layout),inventory(inventory),chat(chat),expbar(expbar) {}

void LayoutManager::decodeInventoryMessage(std::vector<uint32_t> message){
    if (message[1] == 0){
        inventory.addImage(message[2]);
    }
    if (message[1] == 1){
        inventory.removeImage(message[2]);
    }
    if (message[1] == 2){
        inventory.equip(message[2]);
    }
}

void LayoutManager::decodeStateMessage(std::vector<uint32_t> message){
    if (message[1] == 0){
        layout.changeGold(message[2]);
    }
    if (message[1] == 1){
        layout.changeLife(message[2],message[3]);
    }
    if (message[1] == 2){
        layout.changeMana(message[2],message[3]);
    }
    if (message[1] == 3){
        layout.changeLevel(message[2]);
    }
    if (message[1] == 4){
        expbar.changeExp(message[2],message[3]);
    }
}

void LayoutManager::decodeChatMessage(std::vector<uint32_t> message){
    std::stringstream recvd_message;
    if (message[1] == 0){
        recvd_message << "El jugador " << message[2] << " provoco un daño de " << message[3];
    }
    if (message[1] == 1){
        recvd_message << "El jugador " << message[2] << " recibió " << message[3] << " de daño";
    }
    if (message[1] == 2){
        recvd_message << "El jugador " << message[2] << " recuperó " << message[3] << " puntos de vida";
    }
    if (message[1] == 3){
        recvd_message << " Se le avisa al jugador" << message[2] << " que el contrincante esquivo el ataque";
    }
    if (message[1] == 4){
        recvd_message << "El jugador " << message[2] << " esquivo el ataque";
    }
    if (message[1] == 5){
        for (unsigned int i = 2; i < message.size(); i++){
            recvd_message << (char) message[i];
        }
    }
    if (message[1] == 6){
        recvd_message << "El jugador " << message[2] << " gano " << message[3] << " de experiencia";
    }
    if (message[1] == 7){
        recvd_message <<  "El jugador " << message[2] << " subió de nivel";
    }
    chat.addMessage(recvd_message.str());
}