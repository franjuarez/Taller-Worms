#include "hit_upclose.h"
#include "../constants_game.h"

HitUpclose::HitUpclose(int wormID) : Command(NO_TEAM_NEEDED, wormID), wormID(wormID) {}

bool HitUpclose::executeCommand(GameWorld& gameWorld) {
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