#include "ModelController.h"
#include <exception>

#define MOVE_ENTITY 0
#define CREATE_NPC 1
#define CREATE_PLAYER 2
#define CREATE_DROP 3
#define DESTROY_ENTITY 4
#define CHANGE_ENTITY_STATE 5
#define CHANGE_ENTITY_EQUIP 6

ModelController::ModelController(EntityManager &anEntityManager, 
                                 ProtMsgQueue &aMsgQueue) : 
                                        entityManager(anEntityManager),
                                        msgQueue(aMsgQueue) {}

ModelController::~ModelController() {}

void ModelController::run(std::atomic<bool> &closed) {
    while (!msgQueue.isEmpty()) {
        std::vector<uint32_t> event = msgQueue.pop();
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
            entityManager.addNPC((NPCType)event[2], event[1], event[3], 
                                 event[4]);
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
        
        default:
            break;
    }
}
