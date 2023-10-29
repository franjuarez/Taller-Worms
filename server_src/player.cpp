#include "player.h"

Player::Player(GameLobby& gameLobby, Socket&& peer) : 
gameLobby(gameLobby), protocol(std::move(peer)), 
sender(protocol, playerQueue), receiver(protocol) {
    playerQueue.push(gameLobby);
}

Player::~Player() {}