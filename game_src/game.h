#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "worm.h"

class Game {

protected:
    std::vector<std::string> mapNames = {"Aloha: devuelve lo de la clase madre",};
    std::vector<Worm*> worms = {};
    int wormPlayingID = 0;
    int team = 0;
public: 
    Game(std::vector<std::string> mapNames, int team) : mapNames(mapNames), team(team) {}
    Game(int wormPlayingID) : wormPlayingID(wormPlayingID) {} 
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
        return 0;
    }
    virtual int getWormPlayingID() {
        return 0;
    }

};
#endif 
