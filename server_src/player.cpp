#include "player.h"

Player::Player(GameLobby* gameLobby, Socket&& peer, Queue<Command*>& commandQueue) : 
protocol(std::move(peer)), 
sender(gameLobby->getTeam(), protocol, playerQueue, talking), 
receiver(protocol, commandQueue, talking), 
commandsQueue(commandQueue), 
playerQueue(90) {
    playerQueue.push(gameLobby);
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
