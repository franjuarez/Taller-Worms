#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm_dto.h"
#include "weapons_dto.h"

#include "../shared_src/protocol.h"
#include "serializable.h"

#include <iostream>
#include <vector>
#include <atomic>

class Protocol;

class GameDynamic : public Serializable {

private:
    int wormPlayingID;
    std::vector<WormDTO> worms;
    std::vector<WeaponDTO> proyectiles;

public: 
    GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::vector<WeaponDTO> proyectiles);
    void send(Protocol& protocol);
    void addWorms(std::vector<WormDTO>worms); // should change to adding all worms in one to avoid a RC
    std::vector<WormDTO> getWorms();
    std::vector<WeaponDTO> getProjectiles();
    int getWormPlayingID();
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
