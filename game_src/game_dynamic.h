#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm_dto.h"
#include "projectile_dto.h"

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
    std::vector<ProjectileDTO> proyectiles;

public: 
    // va a tener que ser creado ya con el vect de worms parra que no chille la herencia
    GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::vector<ProjectileDTO> proyectiles);
    void send(Protocol& protocol);
    void addWorms(std::vector<WormDTO>worms); // should change to adding all worms in one to avoid a RC
    std::vector<WormDTO> getWorms();
    std::vector<ProjectileDTO> getProjectiles();
    int getWormPlayingID();
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
