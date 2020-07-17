#include "headers/ClientConnector.h"
#include "headers/ClientInitializer.h"

#define ERROR 1
#define SUCCESS 0
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        ClientConnector clientConnector;

        LogInController logInController(argc, argv, clientConnector);
        if (logInController.run() == -1){
            return ERROR;
        }

        ClientInitializer initializer;        
        initializer.run(logInController, clientConnector);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return ERROR;
    } catch (...) {
        std::cerr << "Error client: unknown" << '\n';
    }

    return SUCCESS;
}
