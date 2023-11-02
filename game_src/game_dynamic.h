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
    std::vector<Worm> worms;

public: 
    // va a tener que ser creado ya con el vect de worms parra que no chille la herencia
    GameDynamic(int wormPlayingID, std::vector<Worm>worms);
    void addWorms(std::vector<Worm>worms) override; // should change to adding all worms in one to avoid a RC
    void setWormPlayingID(int id);
    std::vector<Worm> getWorms() override;
    int getNumberOfWorms() override; 
    int getWormPlayingID() override;
    ~GameDynamic();
};
#endif
