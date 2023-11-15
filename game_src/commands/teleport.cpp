#include "teleport.h"
#include "../constants_game.h"


Teleport::Teleport(int wormID, Position pos) : Command(NO_TEAM_NEEDED, wormID), wormID(wormID),
pos(pos) {}

void Teleport::executeCommand(GameWorld& gameWorld) {
    gameWorld.teleportWorm(wormID, pos.getX(), pos.getY());
}

void Teleport::send(Protocol& protocol) {
    protocol.sendTeleport(this);
}

int Teleport::getID() {
    return this->wormID;
}

float Teleport::getX() {
    return this->pos.getX();
}

float Teleport::getY() {
    return this->pos.getY();
}

Teleport::~Teleport() {}