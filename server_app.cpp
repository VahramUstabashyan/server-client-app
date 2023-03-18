#include <iostream>
#include <string>
#include <memory>

#include "server/Server.hpp"


int main(int argc, char** argv) {
   std::string ip = "0.0.0.0";
   int port = 55555;

   if (argc == 3) {
      ip = argv[1];
      port = std::stoi(argv[2]);
   } else if (argc == 1) {
      std::cout << "IP and port set to " << ip << " and " << port << " respectively." << std::endl;
   } else {
      std::cout << "Usage: " << argv[0] << std::endl;
      std::cout << "   OR: " << argv[0] << " <IP> <PORT>" << std::endl;
      exit(0);
   }

    std::cout << "This is server application." << std::endl;
    std::cout << "Enter 'quit' to stop." << std::endl;

    auto server = std::make_shared<Server>(ip, port);

    bool quit = false;
    while (!quit) {
        std::cout << "server@" << ip << ":" << port << "$ ";
        std::string input;
        std::cin >> input;
        quit = input == "quit";
    }
}
