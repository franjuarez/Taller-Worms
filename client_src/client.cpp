#include "client.h"
#include "../shared_src/constants.h"

#include <iostream>

Client::Client(const std::string& hostname, const std::string& servname) : protocol(hostname, servname)
, sender(protocol, std::ref(commandsQueue))
, receiver(protocol, std::ref(gameStatusQueue)) {}

// Game& Client::getGameStatus() {
//     gameStatusQueue.try_pop(gameStatus);
//     return gameStatus;
// }

void Client::start() {
    try {
        sender.start();
        receiver.start();

        sender.join();
        receiver.join();
    } catch (...) {
        std::cout << "AAAAAAAAAAAAAAA\n";
    }
}

// void Client::execute(Command& command) {
//     commandsQueue.push(command);
// }


Client::~Client(){}
