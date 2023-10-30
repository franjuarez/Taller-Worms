#include "player.h"

Player::Player(GameLobby& gameLobby, Socket&& peer, Queue<Command>& commandQueue, StatusBroadcaster& statusBroadcaster) : 
gameLobby(gameLobby), protocol(std::move(peer)), statusBroadcaster(statusBroadcaster), 
sender(gameLobby.getTeam(), protocol, statusBroadcaster, talking), 
receiver(protocol, commandQueue, talking), commandsQueue(commandQueue) {
    playerQueue.push(gameLobby);
    statusBroadcaster.addPlayer(gameLobby.getTeam(), &playerQueue);
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
