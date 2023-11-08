#include "client.h"

#include <iostream>

Client::Client(const std::string& hostname, const std::string& servname) : protocol(hostname, servname)
, gameStatusQueue(900)
, commandsQueue(900)
, sender(protocol, std::ref(commandsQueue), keepTalking)
, receiver(protocol, std::ref(gameStatusQueue), keepTalking) {
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
        std::cout << "Error desconocido en start\n";
    }
}

void Client::kill() {
    keepTalking = false;
    protocol.boom();
    commandsQueue.close();
    gameStatusQueue.close();
    join();
}

void Client::join() {
    receiver.join();
    sender.join();
}

void Client::execute(Command* command) {
    commandsQueue.push(command);
}


Client::~Client(){}
