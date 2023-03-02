#include <iostream>
#include <string>
#include <memory>

#include "Server.hpp"


int main() {
    std::cout << "This is server application." << std::endl;
    std::cout << "Enter 'quit' to stop." << std::endl;

    auto server = std::make_unique<Server>("0.0.0.0", 8080);

    bool quit = false;
    while (!quit) {
        std::string input;
        std::cin >> input;
        quit = input == "quit";
    }
}
