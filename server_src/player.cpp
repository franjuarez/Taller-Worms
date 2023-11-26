#include "player.h"
#include <memory>

Player::Player(Protocol& peer, Queue<std::shared_ptr<Command>>& commandQueue, std::shared_ptr<GameMap> gameMap) : 
protocol(std::move(peer.getSocket())), 
sender(protocol, playerQueue, talking), 
receiver(protocol, commandQueue, talking), 
commandsQueue(commandQueue), 
playerQueue(90) {
    playerQueue.push(gameMap);
    std::shared_ptr<GameDynamic> gameDynamic = std::make_shared<GameDynamic>(GameDynamic(-1, gameMap->getWorms(), {}));
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
    playerQueue.close();
    protocol.boom();
}

bool Player::isAlive() {
    return talking;
}

Player::~Player() {}
