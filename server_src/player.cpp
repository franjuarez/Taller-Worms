#include "player.h"

Player::Player(Socket&& peer, Queue<Command*>& commandQueue, GameMap* gameMap) : 
protocol(std::move(peer)), 
sender(protocol, playerQueue, talking), 
receiver(protocol, commandQueue, talking), 
commandsQueue(commandQueue), 
playerQueue(90) {
    playerQueue.push(gameMap);
    GameDynamic* gameDynamic = new GameDynamic(-1, gameMap->getWorms(), {});
    playerQueue.push(gameDynamic);
}

Queue<Serializable*>* Player::getPlayerQueue() {
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
