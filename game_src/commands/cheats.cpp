
#include "cheats.h"
#include "../constants_game.h"


Cheats::Cheats(int wormID, int cheatID) : Command(wormID), wormID(wormID), cheatID(cheatID) {}

bool Cheats::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    // needsMove = needsMove;
    if (cheatID == ADD_HEALTH) {
        gameWorld.addHealthToWorm(wormID); 
    } else if (cheatID == ALL_WEAPONS) {
        gameWorld.wormGetAllWeapons(wormID);
    } else if (cheatID == ALL_INVINCIBLE) {
        gameWorld.toggleInvincible();
    } else if (cheatID == STOP_TURN) {
        *cheatOn = true;
    } else if (cheatID == RENEW_TURN) {
        *cheatOn = false;
    }
    return needsMove;
}

void Cheats::send(Protocol& protocol) {
    protocol.sendCommand(this);
}

int Cheats::getID() {
    return this->wormID;
}

int Cheats::getCheatID() {
    return this->cheatID;
}

int Cheats::getComType() {
    return this->commandType;
}

Cheats::~Cheats() {}