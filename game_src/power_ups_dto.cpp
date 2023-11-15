#include "power_ups_dto.h"


PowerUps::PowerUps(ExplosivesDTO content, Position pos) : content(content) , pos(pos) {}


float PowerUps::getX() {
    return pos.getX();
}

float PowerUps::getY() {
    return pos.getY();
}

ExplosivesDTO PowerUps::getContent() {
    return content;
}

PowerUps::~PowerUps() {}