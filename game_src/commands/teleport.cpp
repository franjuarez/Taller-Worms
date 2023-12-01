#include "teleport.h"
#include "../constants_game.h"


Teleport::Teleport(int wormID, Position pos) : Command(wormID), wormID(wormID),
pos(pos) {}

bool Teleport::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    return gameWorld.teleportWorm(wormID, pos.getX(), pos.getY());
}

void Teleport::send(Protocol& protocol) {
    protocol.sendCommand(this);
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

int Teleport::getComType() {
    return this->commandType;
}

Teleport::~Teleport() {}