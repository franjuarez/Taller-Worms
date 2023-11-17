#include "player.h"

Player::Player(Socket&& peer, Queue<Command*>& commandQueue, Serializable* gameMap) : 
protocol(std::move(peer)), 
sender(protocol, playerQueue, talking), 
receiver(protocol, commandQueue, talking), 
commandsQueue(commandQueue), 
playerQueue(90) {
    playerQueue.push(gameMap);
    GameDynamic* gameDynamic = new GameDynamic(-1, {}, {});
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
}

bool Player::isAlive() {
    return talking;
}

Player::~Player() {}
