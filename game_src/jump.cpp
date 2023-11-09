#include "commands.h"
#include "jump.h"
#include "constants_game.h"

Jump::Jump(int id, int dir) : Command(NO_TEAM_NEEDED, id), wormID(id), dir(dir) {}

void Jump::executeCommand(GameWorld& gameWorld) {
    std::cout << "exec jump\n";
    if (dir == FORWARD_DIR) {
        gameWorld.jumpForwardWorm(wormID);
    } else if (dir == BACKWARD_DIR) {
        gameWorld.jumpBackwardsWorm(wormID);
    } else{
        throw std::runtime_error("Invalid direction!");
    }
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