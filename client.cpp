#include "ClientConnector.h"
#include "MainWindow.h"
#include "MessageQueue.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "Camera.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "ModelController.h"
#include "Renderer.h"
#include <exception>
#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) return 1; //SACAR ESTO
        ClientConnector clientConnector(argv[1], argv[2]); //CAMBIAR, PASAR DE OTRA FORMA EL IP Y SERVICE
        MainWindow mainWindow;
        MessageQueue senderQueue;
        MessageQueue receiverQueue;
        SDL_Renderer *renderer = mainWindow.getRenderer();

        Player player = clientConnector.getPlayer(renderer);
        MainMap mainMap = clientConnector.getMainMap(renderer);
        Sender sender = clientConnector.getSender(senderQueue);
        Receiver receiver = clientConnector.getReceiver(receiverQueue);

        Layout layout(renderer);
        GraphicInventory gInventory(renderer);
        MiniChat miniChat(renderer);
        ExpBar expBar(renderer);

        Camera camera(player.getPosX(), player.getPosY()); //quizas sea mejor cambiar esto

        EntityManager entityManager(renderer, player, player.getID());

        EventManager eventManager(entityManager, player.getID(), senderQueue);
        ModelController modelController(entityManager, receiverQueue);
        Renderer renderer(camera, player, mainMap, entityManager, 
                          renderer, layout, gInventory, 
                          miniChat, expBar);
        /*try
            sender.run
            receiver.run
            modelcontroller.run
            renderer.run
            eventmanager.run
        catch ()
            sender.join
            receiver.join
            eventmanager.join
            modelcontroller.join
        */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return ERROR;
    } catch (...) {
        std::cerr << "Error: unknown" << '\n';
    }

    return SUCCESS;
}
