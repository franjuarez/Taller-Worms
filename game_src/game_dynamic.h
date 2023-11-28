#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm_dto.h"
#include "explosives_dto.h"
#include "supply_box_dto.h"

#include "constants_game.h"

#include "../shared_src/protocol.h"
#include "serializable.h"

#include <iostream>
#include <vector>
#include <atomic>

class Protocol;

class GameDynamic : public Serializable {

private:
    int wormPlayingID;
    int winnerTeam = PLAYING;
    int status;
    std::vector<WormDTO> worms;
    std::unordered_map<int, ExplosivesDTO> explosives;
    std::unordered_map<int, SupplyBoxDTO> supplyBox;
    std::vector<uint32_t> teamsHealth;

public: 
    //martu no me mates por esta linea 
    GameDynamic();
    GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives, std::unordered_map<int, SupplyBoxDTO> supplyBox);
    GameDynamic(int wormPlayingID, int status, int winnerTeam, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives, std::unordered_map<int, SupplyBoxDTO> supplyBox, std::vector<uint32_t> teamsHealth);

    void send(Protocol& protocol);
    void addWorms(std::vector<WormDTO>worms);

    std::vector<WormDTO> getWorms();
    std::unordered_map<int, ExplosivesDTO> getExplosives();

    int getWormPlayingID();
    void setWormPlayingID(int wormPlayingID);

    int getWinnerTeam();
    void setWinnerTeam(int winnerTeam);

    void setTeamsHealth(std::vector<uint32_t> teamsHealth);
    std::vector<uint32_t> getTeamsHealth();

    uint32_t getTeamHealth(int team);
    int getStatus();
    void setStatus(int status);

    std::unordered_map<int, SupplyBoxDTO> getSupplyBox();
    
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
