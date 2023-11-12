#include "power_ups_dto.h"


PowerUps::PowerUps(WeaponDTO content, Position pos) : content(content) , pos(pos) {}


float PowerUps::getX() {
    return pos.getX();
}

float PowerUps::getY() {
    return pos.getY();
}

WeaponDTO PowerUps::getContent() {
    return content;
}

PowerUps::~PowerUps() {}