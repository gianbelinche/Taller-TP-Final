#include "ModelController.h"
#include "EmptyException.h"
#include <exception>
#include <iostream>

#define MOVE_ENTITY 0
#define CREATE_NPC 1
#define CREATE_PLAYER 2
#define CREATE_DROP 3
#define DESTROY_ENTITY 4

ModelController::ModelController(EntityManager &anEntityManager, 
                                 MessageQueue &aMsgQueue) : 
                                        entityManager(anEntityManager),
                                        msgQueue(aMsgQueue) {}

ModelController::~ModelController() {}

void ModelController::run() {
    try
    {
        while (true) {
            std::vector<uint32_t> event = msgQueue.pop();
            this->handle(event);
        }
    } catch(const EmptyException& e) {
        // Se cerró correctamente
    } catch(const std::exception& e) {
        // Se cerró inesperadamente y cierro cola para avisar a Receiver
        std::cerr << e.what() << '\n';
        msgQueue.close();
    } catch(...) {
        // Se cerró inesperadamente y cierro cola para avisar a Receiver
        std::cerr << "Error ModelController: unkown" << '\n';
        msgQueue.close();
    }
}

void ModelController::handle(std::vector<uint32_t> &event) {
    switch (event[0]) {
        case MOVE_ENTITY:
            entityManager.moveEntity(event[1], (MovementType)event[2]);
            break;

        case CREATE_NPC:
            entityManager.addNPC((NPCType)event[2], event[1], event[3], event[4]);
            break;

        case CREATE_PLAYER:
            entityManager.addPlayer((PlayerRace)event[2], event[1], event[3], event[4], event[5]);
            break;

        case CREATE_DROP:
            entityManager.addDrop((ItemType)event[2], event[1], event[3], event[4]);
            break;

        case DESTROY_ENTITY:
            entityManager.destroyEntity(event[1]);
            break;
        
        default:
            break;
    }
}
