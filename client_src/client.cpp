#include "client.h"

#include <iostream>

Client::Client(std::shared_ptr<InfoStruct> infoStruct) : infoStruct(infoStruct)
, gameStatusQueue(900)
, commandsQueue(900)
, sender(infoStruct->prot, std::ref(commandsQueue), keepTalking)
, receiver(infoStruct->prot, std::ref(gameStatusQueue), keepTalking) {
    lastGameStatus = NULL;
}

std::shared_ptr<Serializable> Client::getGameStatus() {
    try {
        if (!lastGameStatus) {
            lastGameStatus = gameStatusQueue.pop();
            return this->lastGameStatus;
        }
        while (gameStatusQueue.try_pop(this->lastGameStatus)) {}
        return this->lastGameStatus;
    } catch (const ClosedQueue& e) {
        throw ClientClosed();
    }
}

void Client::start() {
    try {
        sender.start();
        receiver.start();
    } catch (std::exception& e) {
        std::cout << "Error in client: " << e.what() << std::endl;
    }
}

void Client::kill() {
    keepTalking = false;
    infoStruct->prot.boom();
    commandsQueue.close();
    gameStatusQueue.close();
    join();
}

void Client::join() {
    receiver.join();
    sender.join();
}

void Client::execute(std::shared_ptr<Command> command) {
    commandsQueue.push(command);
}


Client::~Client(){}
