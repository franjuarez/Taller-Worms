#include "throw_grenade.h"

#include "../constants_game.h"
#include "command.h"


ThrowGrenade::ThrowGrenade(int type, int wormID, int dir, float angle, float power, int timer) : Command(wormID),
type(type), wormID(wormID),dir(dir), angle(angle), power(power), timer(timer) {}


bool ThrowGrenade::executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) {
    *cheatOn = *cheatOn;
    if (needsMove) {
        return true;
    }
    if (type == RED_GRENADE) {
        return gameWorld.wormThrowRedGrenade(wormID, angle, dir, power, timer);
    } else if (type == GREEN_GRENADE) {
        return gameWorld.wormThrowGreenGrenade(wormID, angle, dir, power, timer);
    } else if (type == BANANA) {
        return gameWorld.wormThrowBanana(wormID, angle, dir, power, timer);
    }
    return false;
}

void ThrowGrenade::send(Protocol& protocol) {
    protocol.sendCommand(this);
}

int ThrowGrenade::getType() {
    return type;
}

int ThrowGrenade::getID() {
    return this->wormID;
}

int ThrowGrenade::getDir() {
    return this->dir;
}

float ThrowGrenade::getAngle() {
    return this->angle;
}

float ThrowGrenade::getPower() {
    return this->power;
}

int ThrowGrenade::getTimer() {
    return this->timer;
}

int ThrowGrenade::getComType() {
    return this->commandType;
}

ThrowGrenade::~ThrowGrenade() {}