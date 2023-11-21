
#include "cheats.h"
#include "../constants_game.h"


Cheats::Cheats(int wormID, int cheatID, int health) : Command(wormID), wormID(wormID), cheatID(cheatID), health(health) {}

bool Cheats::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    if (cheatID == CERO_GRAVITY) {
        gameWorld.ceroGravity();
    } else if (cheatID == ADD_HEALTH) {
        gameWorld.addHealthToWorm(wormID, health);
    } else if (cheatID == ALL_WEAPONS) {
        gameWorld.wormGetAllWeapons(wormID);
    } else if (cheatID == ALL_INVINCIBLE) {
        gameWorld.makeWormsInvincible();
    } else if (cheatID == STOP_TURN) {
        *cheatOn = true;
    } else if (cheatID == RENEW_TURN) {
        *cheatOn = false;
    }
    return false;
}

void Cheats::send(Protocol& protocol) {
    protocol.sendCheats(this);
}

int Cheats::getID() {
    return this->wormID;
}

int Cheats::getHealth() {
    return this->health;
}

int Cheats::getCheatID() {
    return this->cheatID;
}

Cheats::~Cheats() {}