#include "client.h"
#include "../shared_src/constants.h"

#include <iostream>

Client::Client(const std::string& hostname, const std::string& servname) : protocol(hostname, servname), gameStatus()
, sender(protocol, std::ref(commandsQueue))
, receiver(protocol, std::ref(gameStatusQueue)) {
}

Game& Client::getGameStatus() {
    gameStatusQueue.try_pop(gameStatus);
    return gameStatus;
}

void Client::run() {
    sender.start();
    receiver.start();
}

void Client::execute(Command& command) {
    commandsQueue.push(command);
}


Client::~Client(){}
