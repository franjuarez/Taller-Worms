#include "jump.h"
#include "../constants_game.h"

Jump::Jump(int id, int dir) : Command(id), wormID(id), dir(dir) {}

bool Jump::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    *cheatOn = *cheatOn;
    if (dir == FORWARD_DIR) {
        gameWorld.jumpForwardWorm(wormID);
    } else if (dir == BACKWARD_DIR) {
        gameWorld.jumpBackwardsWorm(wormID);
    } else{
        throw std::runtime_error("Invalid direction!");
    }
    return false;
}

void Jump::send(Protocol& protocol) {
    protocol.sendJump(this);
}

int Jump::getID() {
    return this->wormID;
}

int Jump::getDir() {
    return this->dir;
}

Jump::~Jump() {}