#include "move.h"
#include "../constants_game.h"


Move::Move(int id, int dir) : Command(id), wormID(id), dir(dir) {}

bool Move::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    // needsMove = needsMove;
    gameWorld.moveWorm(this->wormID, this->dir);
    return needsMove;
}

void Move::send(Protocol& protocol) {
    protocol.sendCommand(this);
}

int Move::getID() {
    return this->wormID;
}

int Move::getDir() {
    return this->dir;
}

int Move::getComType() {
    return this->commandType;
}

Move::~Move() {}