#include "launch_bazooka.h"
#include "../constants_game.h"
#include "command.h"


LaunchRocket::LaunchRocket(int type, int wormID, int dir, float angle, float power) : Command(wormID), type(type),
wormID(wormID),dir(dir), angle(angle), power(power) {}


bool LaunchRocket::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    if (type == BAZOOKA) {
        return gameWorld.wormLaunchBazooka(wormID, angle, dir, power);
    } else if (type == MORTAR) {
        return gameWorld.wormLaunchMortar(wormID, angle, dir, power);
    }
    return false;
}

void LaunchRocket::send(Protocol& protocol) {
    protocol.sendCommand(this);
}

int LaunchRocket::getType() {
    return type;
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

int LaunchRocket::getComType() {
    return this->commandType;
}

LaunchRocket::~LaunchRocket() {}