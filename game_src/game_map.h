#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "position.h"
#include "beam.h"
#include "game.h"

#include <iostream>
#include <vector>
#include <string>

class GameMap : public Game{

private:
    int numberOfBeams;
    std::vector<Beam> beamsMap;
    std::string mapName;

public:
    GameMap(int numberOfBeams, std::string mapName);
    void addBeam(int id, Beam beam);
    std::string getMapName() override;
    std::vector<Beam> getBeams(int) override;
    int getNumberOfBeams() override;
    ~GameMap();
};
#endif
