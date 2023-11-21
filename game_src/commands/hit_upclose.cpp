#include "hit_upclose.h"
#include "../constants_game.h"

HitUpclose::HitUpclose(int wormID, int dir) : Command(wormID), wormID(wormID), dir(dir) {}

bool HitUpclose::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    *cheatOn = *cheatOn;
    gameWorld.wormHitWithBat(wormID, dir);
    return true;
}

void HitUpclose::send(Protocol& protocol) {
    protocol.sendHitUpclose(this);
}

int HitUpclose::getID() {
    return this->wormID;
}

int HitUpclose::getDir() {
    return this->dir;
}

HitUpclose::~HitUpclose() {}