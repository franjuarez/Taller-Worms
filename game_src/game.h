#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "worm.h"

class Game {

protected:
    std::vector<std::string> mapNames = {};
    std::vector<Worm*> worms = {};

public: 
    Game() {}
    ~Game() {}

    virtual std::vector<std::string>& getMapNames() {
        return mapNames;
    }
    virtual int getTeam() {
        return 0;
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
