
#include "beam_dto.h"
#include <iostream>

BeamDTO::BeamDTO(int id, int lenght, Position& pos1, Position& pos2) 
: id(id), beamLength(lenght), position1(pos1), position2(pos2) {}

int BeamDTO::getId() {
    return this->id;
}

Position BeamDTO::getPosition1() {
    return this->position1;
}

Position BeamDTO::getPosition2() {
    return this->position2;
}

int BeamDTO::getBeamLength() {
    return this->beamLength;
}

BeamDTO::~BeamDTO() {}