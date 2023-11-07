#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "position.h"
#include "serializable.h"
#include "../shared_src/protocol.h"


#include <iostream>
#include <vector>
#include <string>

class Protocol;
class GameMap : public Serializable{

private:
    int numberOfBeams;
    std::string mapName;
    std::vector<BeamDTO> beamsMap;
    // std::vector<WormDTO> worms;
public:
    GameMap(int numberOfBeams, std::string mapName, std::vector<BeamDTO> beamsMap);
    void addBeam(int id, BeamDTO beam);
    std::string getMapName();
    std::vector<BeamDTO> getBeams(int);
    int getNumberOfBeams();
    void send(Protocol& protocol);
    ~GameMap();
};
#endif
