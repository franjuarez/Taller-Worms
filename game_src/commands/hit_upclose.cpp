#include "hit_upclose.h"
#include "../constants_game.h"

HitUpclose::HitUpclose(int wormID) : Command(wormID), wormID(wormID) {}

bool HitUpclose::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    *cheatOn = *cheatOn;
    gameWorld.wormHitWithBat(wormID);
    return true;
}

void HitUpclose::send(Protocol& protocol) {
    protocol.sendHitUpclose(this);
}

int HitUpclose::getID() {
    return this->wormID;
}

HitUpclose::~HitUpclose() {}