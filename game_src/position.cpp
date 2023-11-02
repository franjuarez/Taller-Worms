#include "position.h"

#include <iostream>


Position::Position(float x, float y) : x(x), y(y) {}

float Position::getX() {
    return this->x;
}

float Position::getY() {
    return this->y;
}

void Position::setX(float x) {
    this->x = x;
}

void Position::setY(float y) {
    this->y = y;
}

Position::~Position() {}