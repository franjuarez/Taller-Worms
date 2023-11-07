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
    std::vector<Beam> beamsMap;

public:
    GameMap(int numberOfBeams, std::string mapName, std::vector<Beam> beamsMap);
    void addBeam(int id, Beam beam);
    std::string getMapName();
    std::vector<Beam> getBeams(int);
    int getNumberOfBeams();
    void send(Protocol& protocol);
    ~GameMap();
};
#endif
