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
