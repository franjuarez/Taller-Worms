
#include "beam_dto.h"
#include <iostream>

BeamDTO::BeamDTO(int lenght, Position pos, float angle) 
: beamLength(lenght), position(pos), angle(angle) {}

Position BeamDTO::getPosition() {
    return this->position;
}

float BeamDTO::getAngle() {
    return this->angle;
}

int BeamDTO::getBeamLength() {
    return this->beamLength;
}

float BeamDTO::getX() {
    return this->position.getX();
}

float BeamDTO::getY() {
    return this->position.getY();
}

BeamDTO::~BeamDTO() {}