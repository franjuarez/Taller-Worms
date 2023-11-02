#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm.h"
#include "../game_src/game.h"


#include <iostream>
#include <vector>
#include <atomic>


class GameDynamic : public Game {

private:
    int wormPlayingID;
    std::vector<Worm*> worms;

public: 
    GameDynamic(int wormPlayingID);
    void addWorms(std::vector<Worm*>worms); // should change to adding all worms in one to avoid a RC
    void setWormPlayingID(int id);
    // setDynamic to set both the vector and the current player
    std::vector<Worm*> getWorms() override;
    int getNumberOfWorms() override; 
    int getWormPlayingID() override;
    ~GameDynamic();
};
#endif
