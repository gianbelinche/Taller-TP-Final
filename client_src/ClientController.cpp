#include "ClientController.h"

ClientController::ClientController(Receiver &aReceiver, Sender &aSender, 
                                   ModelController &aModelController, 
                                   EventManager &anEventManager, 
                                   Renderer &aRenderer, 
                                   ClientConnector &aClientConnector) : 
                                        receiver(aReceiver), sender(aSender),
                                        modelController(aModelController),
                                        eventManager(anEventManager),
                                        renderer(aRenderer),
                                        clientConnector(aClientConnector) {}

ClientController::~ClientController() {
    receiver.join();
    sender.join();
    renderer.join();
}

void ClientController::run() {
    receiver.start();
    sender.start();
    renderer.start();
    eventManager.run();
    modelController.closeQueue();
    clientConnector.closeSocket();
}
