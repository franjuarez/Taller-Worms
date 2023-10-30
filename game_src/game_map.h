#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "position.h"
#include "beam.h"

#include <iostream>
#include <vector>
#include <string>

class GameMap {

private:
    int numberOfBeams;
    std::vector<Beam*> beamsMap;
    std::string mapName;

public:
    GameMap(int, std::string);
    void addBeam(int, Beam*);
    Position getBeamPosition1(int);
    Position getBeamPosition2(int);
    std::string getMapName();
    Beam getBeam(int);
    // std::vector<Beam*> getBeam(int);
    int getNumberOfBeams();
    int getBeamLength(int);
    ~GameMap();
};
#endif
