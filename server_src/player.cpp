#include "player.h"
#include <memory>
#include "../game_src/constants_game.h"


Player::Player(Socket&& peer, Queue<std::shared_ptr<Command>>& commandQueue, std::shared_ptr<GameMap> gameMap) : 
protocol(std::move(peer)), 
sender(protocol, playerQueue, talking), 
receiver(protocol, commandQueue, talking), 
commandsQueue(commandQueue), 
playerQueue(90) {
    playerQueue.push(gameMap);
    std::shared_ptr<GameDynamic> gameDynamic = std::make_shared<GameDynamic>(GameDynamic(-1, gameMap->getWorms(), {}));
    gameDynamic->setStatus(WAITING);
    playerQueue.push(gameDynamic);
}

Queue<std::shared_ptr<Serializable>>* Player::getPlayerQueue() {
    return &playerQueue;
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
    commandsQueue.close();
    playerQueue.close();
    protocol.boom();
}

bool Player::isAlive() {
    return talking;
}

Player::~Player() {}
