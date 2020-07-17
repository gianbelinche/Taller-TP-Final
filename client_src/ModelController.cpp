#include "headers/ModelController.h"
#include <exception>
#include <iostream>
#define POTION 0
enum state {
    MOVE_ENTITY,
    CREATE_NPC,
    CREATE_PLAYER,
    CREATE_DROP,
    DESTROY_ENTITY,
    CHANGE_ENTITY_STATE,
    CHANGE_ENTITY_EQUIP,
    CHAT,
    INVENTORY,
    LAYOUT_STATE,
    LOGIN,
    SOUND_ATTACK,
    DRINK_POTION,
    TELEPORT,
    ATTACK
};

ModelController::ModelController(EntityManager &anEntityManager, 
                                 ProtMsgQueue &aMsgQueue,
                                 LayoutManager &layoutManager) : 
                                        entityManager(anEntityManager),
                                        msgQueue(aMsgQueue),
                                        layoutManager(layoutManager){}

ModelController::~ModelController() {}

void ModelController::run(std::atomic<bool> &closed) {
    while (!msgQueue.isEmpty()) {
        std::vector<uint32_t> event = std::move(msgQueue.pop());
        this->handle(event);
    }

    if (msgQueue.isClosed()) {
        closed = true;
    }
}

void ModelController::closeQueue() {
    msgQueue.close();
}

void ModelController::handle(std::vector<uint32_t> &event) {
    switch (event[0]) {
        case MOVE_ENTITY:
            entityManager.moveEntity(event[1], (MovementType)event[2]);
            break;

        case CREATE_NPC:
            if (event[2] == 0) {
                entityManager.addNPC((NPCType)event[3], event[1], event[4], 
                                     event[5]);
            } else if (event[2] == 1) {
                entityManager.addMob((MobType)event[3], event[1], event[4], 
                                     event[5]);
            }
            break;

        case CREATE_PLAYER:
            entityManager.addPlayer((PlayerRace)event[2], event[1], event[3], 
                                    event[4], event[5], (EquipType)event[6], 
                                    (EquipType)event[7], (EquipType)event[8], 
                                    (EquipType)event[9]);
            break;

        case CREATE_DROP:
            entityManager.addDrop((ItemType)event[2], event[1], event[3], 
                                  event[4]);
            break;

        case DESTROY_ENTITY:
            entityManager.destroyEntity(event[1]);
            break;

        case CHANGE_ENTITY_STATE:
            entityManager.changeEntityState(event[1], event[2]);
            break;

        case CHANGE_ENTITY_EQUIP:
            entityManager.changeEntityEquipment(event[1], (EquipType)event[3], 
                                                event[2]);
            break;
        
        case INVENTORY:
            layoutManager.decodeInventoryMessage(event);
            break;

        case LAYOUT_STATE:
            layoutManager.decodeStateMessage(event);
            break;

        case CHAT:
            layoutManager.decodeChatMessage(event);
            break;

        case LOGIN:
            break;   

        case SOUND_ATTACK:
            soundEffectPlayer.play(event[1]);
            break;

        case DRINK_POTION:
            soundEffectPlayer.play(POTION);
            break;

        case TELEPORT:
            entityManager.teleportEntity(event[1], event[2], event[3]);

        case ATTACK:
            entityManager.addAttack((AttackType)event[1], event[2], event[3]);
        
        default:
            break;
    }
}
