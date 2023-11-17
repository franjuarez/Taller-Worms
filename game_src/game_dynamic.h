#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm_dto.h"
#include "explosives_dto.h"

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
    std::unordered_map<int, ExplosivesDTO> explosives;

public: 
    GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives);
    void send(Protocol& protocol);
    void addWorms(std::vector<WormDTO>worms);
    std::vector<WormDTO> getWorms();
    std::unordered_map<int, ExplosivesDTO> getExplosives();
    int getWormPlayingID();
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
