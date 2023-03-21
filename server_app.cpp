#include <iostream>
#include <string>
#include <memory>
#include <readline/readline.h>
#include <readline/history.h>

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
    std::string start_str = "server@" + ip + ":" + std::to_string(port) + "$ ";
    while (!quit) {
        std::string input = readline(start_str.c_str());
        if (input.length() > 0) add_history(input.c_str());
        quit = input == "quit";
    }
}
