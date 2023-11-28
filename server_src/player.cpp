#include "player.h"
#include <memory>
#include "../game_src/constants_game.h"
#include "../shared_src/info_struct.h"


Player::Player(std::shared_ptr<InfoStruct> infoStruct, int playerID, Queue<std::shared_ptr<Command>>& commandQueue, StatusBroadcaster& statusBroadcaster , std::shared_ptr<GameMap> gameMap) : 
playerID(playerID),
infoStruct(infoStruct), 
commandsQueue(commandQueue),
playerQueue(90),
statusBroadcaster(statusBroadcaster),
sender(infoStruct->prot, statusBroadcaster, talking, playerID), 
receiver(infoStruct->prot, commandQueue, talking)
{
    playerQueue.push(gameMap);
    std::shared_ptr<GameDynamic> gameDynamic = std::make_shared<GameDynamic>(GameDynamic(-1, gameMap->getWorms(), {}, {}));
    gameDynamic->setStatus(WAITING);
    playerQueue.push(gameDynamic);

    statusBroadcaster.addPlayer(playerID, &playerQueue);
}


void Player::start() {
    sender.start();
    receiver.start();
}

void Player::join(){
    sender.join();
    receiver.join();
}

void Player::kill() {
    talking = false;
    playerQueue.close();
    infoStruct->prot.boom();
}

bool Player::isAlive() {
    return talking;
}

Player::~Player() {}
