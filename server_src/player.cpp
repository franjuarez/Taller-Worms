#include "player.h"

Player::Player(int id, Socket&& peer) : 
id(id), protocol(std::move(peer)), sender(protocol), receiver(protocol) {}

Player::~Player() {}