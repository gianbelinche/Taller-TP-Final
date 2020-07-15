#ifndef __CLIENT_CONTROLLER_H__
#define __CLIENT_CONTROLLER_H__

#include "Receiver.h"
#include "Sender.h"
#include "ModelController.h"
#include "EventManager.h"
#include "Renderer.h"
#include "ClientConnector.h"

class ClientController {
    private:
        Receiver &receiver;
        Sender &sender;
        ModelController &modelController;
        EventManager &eventManager;
        Renderer &renderer;
        ClientConnector &clientConnector;

    public:
        ClientController(Receiver &aReceiver, Sender &aSender, 
                        ModelController &aModelController, 
                        EventManager &anEventManager, Renderer &aRenderer,
                        ClientConnector &aClientConnector);
        ~ClientController();

        ClientController(const ClientController &copy) = delete;

        void run();
};
 
#endif
