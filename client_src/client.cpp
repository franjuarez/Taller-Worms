#include "client.h"
#include "../shared_src/constants.h"

#include <iostream>

Client::Client(const std::string& hostname, const std::string& servname) : protocol(hostname, servname)
, sender(protocol, std::ref(commandsQueue))
, receiver(protocol, std::ref(gameStatusQueue)) {}

GameDynamic Client::getGameStatus() {
    GameDynamic gameStatus(NO_WORM_PLAYING, std::vector<Worm>{});
    while (gameStatusQueue.try_pop(gameStatus)) {};
    std::cout <<  gameStatus.getWorms().at(1).getPosition().getX() << "\n";
    return gameStatus;
}

void Client::start() {
    try {
        sender.start();
        receiver.start();
    } catch (...) {
        std::cout << "AAAAAAAAAAAAAAA\n";
    }
}

void Client::join() {
    sender.join();
    receiver.join();
}

// void Client::execute(Command& command) {
//     commandsQueue.push(command);
// }


Client::~Client(){}
