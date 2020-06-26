#include "ModelController.h"
#include "EmptyException.h"
#include <exception>
#include <iostream>

ModelController::ModelController(EntityManager &anEntityManager, 
                                 MessageQueue &aMsgQueue) : 
                                        entityManager(anEntityManager),
                                        msgQueue(aMsgQueue) {}

ModelController::~ModelController() {}

void ModelController::run() {
    try
    {
        while (true) {
            std::vector<uint32_t> msg = msgQueue.pop();
            /*
            aca hay dos opciones, pasarlo a un protocol o a una
            funcion handle
            */
        }
    } catch(const EmptyException& e) {
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch(...) {
        std::cerr << "Error ModelController: unkown" << '\n';
    }
}
