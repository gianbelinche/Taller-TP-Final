#include "ClientConnector.h"
#include "MainWindow.h"
#include "MessageQueue.h"
#include "MainMap.h"
#include "Sender.h"
#include "Receiver.h"
#include "Camera.h"
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

        Player player = clientConnector.getPlayer(mainWindow.getRenderer());
        MainMap mainMap = clientConnector.getMainMap(mainWindow.getRenderer());
        Sender sender = clientConnector.getSender(senderQueue);
        Receiver receiver = clientConnector.getReceiver(receiverQueue);

        Camera camera(player.getPosX(), player.getPosY()); //quizas sea mejor cambiar esto

        //EntityManager

        //EventManager
        //ModelController
        //Renderer
        /*
        ClientProtocol <- eliminar esta clase (tiene cómo se crea mainmap)
        */
        /*
        try
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
