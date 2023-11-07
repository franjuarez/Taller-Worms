#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm.h"
#include "../shared_src/protocol.h"
#include "serializable.h"

#include <iostream>
#include <vector>
#include <atomic>


class GameDynamic : public Serializable {

private:
    int wormPlayingID;
    std::vector<Worm> worms;

public: 
    // va a tener que ser creado ya con el vect de worms parra que no chille la herencia
    GameDynamic(int wormPlayingID, std::vector<Worm>worms);
    void send(Protocol& protocol);
    void addWorms(std::vector<Worm>worms); // should change to adding all worms in one to avoid a RC
    void setWormPlayingID(int id);
    std::vector<Worm> getWorms();
    int getNumberOfWorms(); 
    int getWormPlayingID();
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
