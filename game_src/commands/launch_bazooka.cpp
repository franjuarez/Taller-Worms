#include "launch_bazooka.h"
#include "../constants_game.h"
#include "command.h"


LaunchRocket::LaunchRocket(int wormID, int dir, float angle, float power) : Command(NO_TEAM_NEEDED, wormID),
wormID(wormID),dir(dir), angle(angle), power(power) {}

void LaunchRocket::executeCommand(GameWorld& gameWorld) {
    gameWorld.wormLaunchBazooka(wormID, angle, dir, power);
}

void LaunchRocket::send(Protocol& protocol) {
    protocol.sendLaunchRocket(this);
}

int LaunchRocket::getID() {
    return this->wormID;
}

int LaunchRocket::getDir() {
    return this->dir;
}

float LaunchRocket::getAngle() {
    return this->angle;
}

float LaunchRocket::getPower() {
    return this->power;
}

LaunchRocket::~LaunchRocket() {}