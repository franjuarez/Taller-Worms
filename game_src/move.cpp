#include "commands.h"
#include "move.h"
#include "constants_game.h"


Move::Move(int id, int dir) : Command(NO_TEAM_NEEDED, id), wormID(id), dir(dir) {}

void Move::executeCommand(GameWorld& gameWorld) {
    std::cout << "exec move\n";
    if (dir == RIGHT_DIR) {
        gameWorld.moveWormRight(wormID);
    } else if (dir == LEFT_DIR) {
        gameWorld.moveWormLeft(wormID);
    } else{
        std::cout << "dir: " << dir << "\n";
        throw std::runtime_error("Invalid direction!");
    }
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