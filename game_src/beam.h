#ifndef BEAM_H
#define BEAM_H


#include "position.h"

class Beam {
private:
    int id;
    int beamLength;
    Position position1; // having both extremes to get the angle :)
    Position position2; 
    // float angle;
public:
    Beam(int, int, Position&, Position&);
    int getId();
    Position getPosition1();
    Position getPosition2();
    int getBeamLength();
    // void calcAngle();
    // float getAngle();
    ~Beam();
};
#endif
