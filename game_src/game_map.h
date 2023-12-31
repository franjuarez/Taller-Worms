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
    int numberTeams;
    std::string mapName;
    std::vector<BeamDTO> beamsMap;
    std::unordered_map<int, WormDTO>worms;

    int serializableType = GAME_MAP;
public:
    GameMap(int team, int numberTeams, std::string mapName, std::vector<BeamDTO> beamsMap, std::unordered_map<int, WormDTO>worms);
    int getTeam();
    void setTeam(int newTeam);
    int getNumberTeams();
    std::string getMapName();
    std::vector<BeamDTO> getBeams();
    std::unordered_map<int, WormDTO> getWorms();
    int getNumberOfBeams();
    int getNumberOfWorms();
    void send(Protocol& protocol);
    int getSerType();
    ~GameMap();
};
#endif
