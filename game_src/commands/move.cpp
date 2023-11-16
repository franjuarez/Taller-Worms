#include "move.h"
#include "../constants_game.h"


Move::Move(int id, int dir) : Command(NO_TEAM_NEEDED, id), wormID(id), dir(dir) {}

bool Move::executeCommand(GameWorld& gameWorld) {
    gameWorld.moveWorm(this->wormID, this->dir);
    return false;
}

void Move::send(Protocol& protocol) {
    protocol.sendMove(this);
}

int Move::getID() {
    return this->wormID;
}

int Move::getDir() {
    return this->dir;
}

Move::~Move() {}