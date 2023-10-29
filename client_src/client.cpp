#include "client.h"
#include "../shared_src/constants.h"


Client::Client(const std::string& servname, const std::string& hostname) :
protocol(servname, hostname), gameStatus()
, sender(protocol, std::ref(commandsQueue))
, receiver(protocol, std::ref(gameStatusQueue)) {}

Game& Client::getGameStatus() {
    gameStatusQueue.try_pop(gameStatus);
    return gameStatus;
}

void Client::execute(Command& command) {
    commandsQueue.push(command);
}

Client::~Client(){}
