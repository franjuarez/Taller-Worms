#include "launch_bazooka.h"
#include "../constants_game.h"
#include "command.h"
#include "../../physics_src/game_world.h"
#include "../../shared_src/protocol.h"


LaunchRocket::LaunchRocket(int type, int wormID, int dir, float angle, float power) : Command(wormID), type(type),
wormID(wormID),dir(dir), angle(angle), power(power) {}


bool LaunchRocket::executeCommand(GameWorld& gameWorld, bool* cheatOn) {
    *cheatOn = *cheatOn;
    if (type == BAZOOKA) {
        return gameWorld.wormLaunchBazooka(wormID, angle, dir, power);
    } else if (type == MORTAR) {
        return gameWorld.wormLaunchMortar(wormID, angle, dir, power);
    }
    
    return false;
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