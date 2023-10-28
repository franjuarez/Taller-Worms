#include "beam.h"

#include <iostream>

Beam::Beam(int id, int lenght, Position& pos1, Position& pos2) 
: id(id), beamLength(lenght), position1(pos1), position2(pos2) {}

int Beam::getId() {
    return this->id;
}

Position Beam::getPosition1() {
    return this->position1;
}

Position Beam::getPosition2() {
    return this->position2;
}

int Beam::getBeamLength() {
    return this->beamLength;
}

Beam::~Beam() {}