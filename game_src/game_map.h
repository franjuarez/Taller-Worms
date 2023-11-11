#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "position.h"
#include "serializable.h"
#include "worm_dto.h"
#include "../shared_src/protocol.h"


#include <iostream>
#include <vector>
#include <string>

class Protocol;

class GameMap : public Serializable{

private:
    int team;
    std::string mapName;
    std::vector<BeamDTO> beamsMap;
    std::vector<WormDTO> worms;
public:
    GameMap(int team, std::string mapName, std::vector<BeamDTO> beamsMap, std::vector<WormDTO> worms);
    int getTeam();
    std::string getMapName();
    std::vector<BeamDTO> getBeams();
    std::vector<WormDTO> getWorms();
    int getNumberOfBeams();
    int getNumberOfWorms();
    void send(Protocol& protocol);
    ~GameMap();
};
#endif
