#include "remote_operated.h"
#include "../constants_game.h"


Teleport::Teleport(int wormID, int type, Position pos) : Command(wormID), wormID(wormID), type(type),
pos(pos) {}

bool Teleport::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    if (type == TELEPORT) {
        return gameWorld.teleportWorm(wormID, pos.getX(), pos.getY());
    } if (type == AIR_ATTACK) {
        return gameWorld.wormCallAirAttack(wormID, pos.getX(), pos.getY());
    }
    return false;
}

void Teleport::send(Protocol& protocol) {
    protocol.sendTeleport(this);
}

int Teleport::getID() {
    return this->wormID;
}

int Teleport::getType() {
    return this->type;
}

float Teleport::getX() {
    return this->pos.getX();
}

float Teleport::getY() {
    return this->pos.getY();
}

Teleport::~Teleport() {}