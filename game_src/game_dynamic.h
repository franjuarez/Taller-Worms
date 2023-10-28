#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm.h"

#include <iostream>
#include <vector>
#include <atomic>


class GameDynamic {

private:
    int wormPlayingID;
    std::vector<Worm*> worms;

public: 
    GameDynamic(int);
    void addWorm(Worm*); // should change to adding all worms in one to avoid a RC
    void setWormPlayingID(int);
    // setDynamic to set both the vector and the current player
    std::vector<Worm*> getWorms();
    int getNumberOfWorms(); 
    int getWormPlayingID();
    ~GameDynamic();
};
#endif
