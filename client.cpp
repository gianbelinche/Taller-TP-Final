#include "MainWindow.h"
#include <exception>
#include <iostream>

int main(int argc, char* args[]) {
    try {
        MainWindow mW;
		mW.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
