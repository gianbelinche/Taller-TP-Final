#include "headers/ClientInitializer.h"

#include "headers/MainWindow.h"
#include "headers/BlockingMsgQueue.h"
#include "headers/ProtMsgQueue.h"
#include "headers/MainMap.h"
#include "headers/Sender.h"
#include "headers/Receiver.h"
#include "headers/Camera.h"
#include "headers/EntityManager.h"
#include "headers/EventManager.h"
#include "headers/ModelController.h"
#include "headers/Renderer.h"
#include "headers/ClientController.h"
#include "headers/LayoutManager.h"
#include "headers/SocketException.h"
#include "headers/ClientConnector.h"
#include "headers/LogInController.h"

#include <arpa/inet.h>
#include <msgpack.hpp>

void ClientInitializer::run(LogInController &logInController, 
                            ClientConnector &clientConnector){
    ClientProtocol clientProtocol;
    MainWindow mainWindow(logInController.getHeigth(),
                        logInController.getWidth());
    
    SDL_Renderer *mainRenderer = mainWindow.getRenderer();
    BlockingMsgQueue senderQueue;
    ProtMsgQueue receiverQueue;

    GraphicInventory gInventory(mainRenderer);
    Player player = std::move(clientConnector.getPlayer(mainRenderer,gInventory));
    MainMap mainMap = std::move(clientConnector.getMainMap(mainRenderer));
    clientConnector.sendReceivedSignal(clientProtocol, player.getID());
    Sender sender = std::move(clientConnector.getSender(senderQueue));
    Receiver receiver = std::move(clientConnector.getReceiver(receiverQueue));

    Layout layout(mainRenderer);
    MiniChat miniChat(mainRenderer);
    ExpBar expBar(mainRenderer);

    LayoutManager layoutManager(layout,gInventory,miniChat,expBar);

    Camera camera(player.getPosX(), player.getPosY(), player.getHeight(), 
                    player.getWidth(),logInController.getHeigth(),
                    logInController.getWidth());

    EntityManager entityManager(mainRenderer, &player, player.getID());

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
}