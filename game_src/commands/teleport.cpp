#include "teleport.h"
#include "../constants_game.h"
#include "../../physics_src/game_world.h"
#include "../../shared_src/protocol.h"

Teleport::Teleport(int wormID, Position pos) : Command(wormID), wormID(wormID),
pos(pos) {}

bool Teleport::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    *cheatOn = *cheatOn;
    return gameWorld.teleportWorm(wormID, pos.getX(), pos.getY());
}

void Teleport::send(Protocol& protocol) {
    protocol.sendTeleport(this);
}

int Teleport::getID() {
    return this->wormID;
}

float Teleport::getX() {
    return this->pos.getX();
}

float Teleport::getY() {
    return this->pos.getY();
}

Teleport::~Teleport() {}