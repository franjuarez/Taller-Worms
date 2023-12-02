#include "remote_operated.h"
#include "../constants_game.h"


RemoteOperated::RemoteOperated(int wormID, int type, Position pos) : Command(wormID), wormID(wormID), type(type),
pos(pos) {}

bool RemoteOperated::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    if (type == REMOTE_OPERATED) {
        return gameWorld.teleportWorm(wormID, pos.getX(), pos.getY());
    } if (type == AIR_ATTACK) {
        return gameWorld.wormCallAirAttack(wormID, pos.getX(), pos.getY());
    }
    return false;
}

void RemoteOperated::send(Protocol& protocol) {
    protocol.sendCommand(this);
}

int RemoteOperated::getID() {
    return this->wormID;
}

int RemoteOperated::getType() {
    return this->type;
}

float RemoteOperated::getX() {
    return this->pos.getX();
}

float RemoteOperated::getY() {
    return this->pos.getY();
}

int RemoteOperated::getComType() {
    return this->commandType;
}

RemoteOperated::~RemoteOperated() {}