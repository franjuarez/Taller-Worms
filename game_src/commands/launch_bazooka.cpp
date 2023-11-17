#include "launch_bazooka.h"
#include "../constants_game.h"
#include "command.h"


LaunchRocket::LaunchRocket(int type, int wormID, int dir, float angle, float power) : Command(NO_TEAM_NEEDED, wormID), type(type),
wormID(wormID),dir(dir), angle(angle), power(power) {}


bool LaunchRocket::executeCommand(GameWorld& gameWorld) {
    if (type == BAZOOKA) {
        gameWorld.wormLaunchBazooka(wormID, angle, dir, power);
    } else if (type == MORTAR) {
        gameWorld.wormLaunchMortar(wormID, angle, dir, power);
    }
    
    return true;
}

void LaunchRocket::send(Protocol& protocol) {
    protocol.sendLaunchRocket(this);
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

LaunchRocket::~LaunchRocket() {}