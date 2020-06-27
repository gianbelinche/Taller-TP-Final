#include "ClientController.h"

ClientController::ClientController(Receiver &aReceiver, Sender &aSender, 
                                   ModelController &aModelController, 
                                   EventManager &anEventManager, 
                                   Renderer &aRenderer) : 
                                        receiver(aReceiver), sender(aSender),
                                        modelController(aModelController),
                                        eventManager(anEventManager),
                                        renderer(aRenderer) {}

ClientController::~ClientController() {
    receiver.join();
    sender.join();
    modelController.join();
    renderer.join();
}

/*
CHEQUEAR EL TEMA DE VER QUE ESTE TODO CERRADO ANTES DE LLEGAR AL
JOIN PARA QUE NO SE QUEDE TRABADO.
VER COMO HACER PARA CERRAR EVENTMANAGER EN CASO DE FALLA.
VER COMO CERRAR CADA UNO EN CASO DE FALLA.
*/

void ClientController::run() {
    receiver.run();
    sender.run();
    modelController.run();
    renderer.run();
    eventManager.run();
}
