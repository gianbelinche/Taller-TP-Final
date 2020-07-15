#include "headers/ClientInitializer.h"

#define ERROR 1
#define SUCCESS 0
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        ClientInitializer initializer;
        initializer.run(argc,argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return ERROR;
    } catch (...) {
        std::cerr << "Error client: unknown" << '\n';
    }

    return SUCCESS;
}
