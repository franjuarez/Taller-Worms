#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "worm.h"
#include "beam.h"

class Game {

protected:
    std::vector<std::string> mapNames = {"Aloha: devuelve lo de la clase madre",};
    std::vector<Worm*> worms = {};
    int wormPlayingID = 0;
    int team = 0;
    int numberOfBeams = 0;
    std::vector<Beam> beamsMap = {};
    std::string mapName = "";
public: 
    Game(std::vector<std::string> mapNames, int team) : mapNames(mapNames), team(team) {}
    Game(int wormPlayingID) : wormPlayingID(wormPlayingID) {} 
    Game(int numberOfBeams, std::string mapName) : numberOfBeams(numberOfBeams), mapName(mapName) {}
    ~Game() {}

    virtual std::vector<std::string>& getMapNames() {
        return mapNames;
    }
    virtual int getTeam() {
        return team;
    }

    virtual std::vector<Worm*> getWorms() {
        return worms;
    }

    virtual int getNumberOfWorms() { 
        return worms.size();
    }
    virtual int getWormPlayingID() {
        return wormPlayingID;
    }
    virtual std::string getMapName() {
        return mapName;
    }
    virtual std::vector<Beam> getBeams(int) {
        return beamsMap;
    }
    virtual int getNumberOfBeams() {
        return numberOfBeams;
    }

};
#endif 
