#include "ClientConnector.h"
#include "MainWindow.h"
#include "BlockingMsgQueue.h"
#include "ProtMsgQueue.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "Camera.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "ModelController.h"
#include "Renderer.h"
#include "ClientController.h"
#include "LayoutManager.h"
#include <exception>
#include <iostream>
#include "SocketException.h"
#include "LogInController.h"

#define ERROR 1
#define SUCCESS 0

#include <arpa/inet.h>
#include <msgpack.hpp>

int main(int argc, char* argv[]) {
    try {
        ClientProtocol clientProtocol;
        ClientConnector clientConnector;
        LogInController logInController(argc, argv, clientConnector);
        if (logInController.run() == -1){
            std::cout << -1;
            return SUCCESS;
        }

        MainWindow mainWindow(logInController.getHeigth(),
                            logInController.getWidth());
        SDL_Renderer *mainRenderer = mainWindow.getRenderer();
        BlockingMsgQueue senderQueue;
        ProtMsgQueue receiverQueue;

        Player player = clientConnector.getPlayer(mainRenderer);
        MainMap mainMap = clientConnector.getMainMap(mainRenderer);
        clientConnector.sendReceivedSignal(clientProtocol, player.getID());
        Sender sender = clientConnector.getSender(senderQueue);
        Receiver receiver = clientConnector.getReceiver(receiverQueue);

        Layout layout(mainRenderer);
        GraphicInventory gInventory(mainRenderer);
        MiniChat miniChat(mainRenderer);
        ExpBar expBar(mainRenderer);

        LayoutManager layoutManager(layout,gInventory,miniChat,expBar);

        Camera camera(player.getPosX(), player.getPosY(), player.getHeight(), 
                      player.getWidth(),logInController.getHeigth(),
                      logInController.getWidth());

        EntityManager entityManager(mainRenderer, player, player.getID());

        EventManager eventManager(entityManager, player.getID(), senderQueue, 
                                  camera, clientProtocol,miniChat, gInventory);
        ModelController modelController(entityManager, receiverQueue,
                                         layoutManager);
        Renderer renderer(camera, player, mainMap, entityManager, 
                          mainRenderer, layout, gInventory, miniChat, expBar,
                          modelController);

        ClientController clientController(receiver, sender, modelController,
                                          eventManager, renderer, clientConnector);
        clientController.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return ERROR;
    } catch (...) {
        std::cerr << "Error client: unknown" << '\n';
    }

    return SUCCESS;
}
