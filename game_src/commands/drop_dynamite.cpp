#include "drop_dynamite.h"
#include "../constants_game.h"


DropDynamite::DropDynamite(int id, int dir) : Command(id), wormID(id), timer(timer) {}

bool DropDynamite::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    return gameWorld.wormDropDynamite(wormID, timer);
}

void DropDynamite::send(Protocol& protocol) {
    protocol.sendDynamite(this);
}

int DropDynamite::getID() {
    return this->wormID;
}

int DropDynamite::getTimer() {
    return this->timer;
}

DropDynamite::~DropDynamite() {}