#include "move.h"
#include "../constants_game.h"


Move::Move(int id, int dir) : Command(NO_TEAM_NEEDED, id), wormID(id), dir(dir) {}

void Move::executeCommand(GameWorld& gameWorld) {
    // std::cout << "exec move\n";
    gameWorld.moveWorm(this->wormID, this->dir);
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