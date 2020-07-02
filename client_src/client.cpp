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
#include "LoginScreen.h"
#include "LoginManager.h"
#include "SocketException.h"

#define ERROR 1
#define SUCCESS 0

#include <arpa/inet.h>
#include <msgpack.hpp>

int main(int argc, char* argv[]) {
    try {
        //if (argc != 3) return 1; //SACAR ESTO
        //ClientConnector clientConnector(argv[1], argv[2]); //CAMBIAR, PASAR DE OTRA FORMA EL IP Y SERVICE
        MainWindow mainWindow;
        SDL_Renderer *mainRenderer = mainWindow.getRenderer();
        BlockingMsgQueue senderQueue;
        ProtMsgQueue receiverQueue;
        ClientProtocol clientProtocol;

        LoginScreen loginScreen(mainRenderer);
        LoginManager loginManager(loginScreen,mainRenderer);
        ClientConnector clientConnector;
        bool connected = false;
        while (!connected){
            try {
                std::vector<std::string> server = loginManager.run();
                clientConnector.connect(server[0].c_str(),server[1].c_str());
            } catch(const SocketException& e){
                loginScreen.showError("Error al conectarse al servidor");
                continue;
            }
            connected = true;
            loginScreen.changeToUserInput();
        }
        

        Player player = clientConnector.getPlayer(mainRenderer);
        MainMap mainMap = clientConnector.getMainMap(mainRenderer);
        Sender sender = clientConnector.getSender(senderQueue);
        Receiver receiver = clientConnector.getReceiver(receiverQueue);

        Layout layout(mainRenderer);
        GraphicInventory gInventory(mainRenderer);
        MiniChat miniChat(mainRenderer);
        ExpBar expBar(mainRenderer);

        LayoutManager layoutManager(layout,gInventory,miniChat,expBar);

        Camera camera(player.getPosX(), player.getPosY(), player.getHeight(), 
                      player.getWidth());

        EntityManager entityManager(mainRenderer, player, player.getID());

        EventManager eventManager(entityManager, player.getID(), senderQueue, 
                                  camera, clientProtocol,miniChat, gInventory);
        ModelController modelController(entityManager, receiverQueue, layoutManager);
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
