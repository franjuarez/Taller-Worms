#ifndef BEAM_DTO_H
#define BEAM_DTO_H

#include "position.h"

class BeamDTO {
private:
    int beamLength;
    Position position; // having both extremes to get the angle :)
    float angle;
public:
    BeamDTO(int lenght, Position pos, float angle);
    Position getPosition();
    int getBeamLength();
    float getAngle();
    ~BeamDTO();
};
#endif
