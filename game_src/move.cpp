#include "commands.h"
#include "move.h"
#include "constants_game.h"


Move::Move(int id) : Command(NO_TEAM_NEEDED, id), wormID(id) {}

void Move::executeCommand() {
    std::cout << "exec move\n";
}

void Move::send(Protocol& protocol) {
    protocol.sendMove(this);
}

int Move::getID() {
    return this->wormID;
}

Move::~Move() {}