#include "client.h"

#include <iostream>

Client::Client(const std::string& hostname, const std::string& servname) : protocol(hostname, servname)
, gameStatusQueue(90)
, commandsQueue(90)
, sender(protocol, std::ref(commandsQueue))
, receiver(protocol, std::ref(gameStatusQueue)) {
    lastGameStatus = NULL;
}

Serializable* Client::getGameStatus() {
    if (!lastGameStatus) {
        lastGameStatus = gameStatusQueue.pop();
    }
    while (gameStatusQueue.try_pop(this->lastGameStatus)) {}
    return this->lastGameStatus;
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

void Client::execute(Command* command) {
    commandsQueue.push(command);
}


Client::~Client(){}
