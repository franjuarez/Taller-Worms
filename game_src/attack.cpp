#include "attack.h"
#include "constants_game.h"
#include "commands.h"


Attack::Attack(int wormID, int dir, float angle, float power) : Command(NO_TEAM_NEEDED, wormID),
wormID(wormID),dir(dir), angle(angle), power(power) {}

void Attack::executeCommand(GameWorld& gameWorld) {
    gameWorld.wormLaunchRocket(wormID, angle, dir, power);
}

void Attack::send(Protocol& protocol) {
    protocol.sendAttack(this);
}

int Attack::getID() {
    return this->wormID;
}

int Attack::getDir() {
    return this->dir;
}

float Attack::getAngle() {
    return this->angle;
}

float Attack::getPower() {
    return this->power;
}

Attack::~Attack() {}