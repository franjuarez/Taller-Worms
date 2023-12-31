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
    int status = WAITING;
    std::unordered_map<int, WormDTO> worms;
    int timer = 0;
    std::unordered_map<int, ExplosivesDTO> explosives;
    std::unordered_map<int, SupplyBoxDTO> supplyBox;
    std::vector<uint32_t> teamsHealth = {};

    int serializableType = GAME_DYNAMIC;
public: 
    GameDynamic();
    GameDynamic(int wormPlayingID, std::unordered_map<int, WormDTO> worms, std::unordered_map<int, ExplosivesDTO> explosives, std::unordered_map<int, SupplyBoxDTO> supplyBox);
    GameDynamic(int wormPlayingID, int status, int winnerTeam, int timer, std::unordered_map<int, WormDTO> worms, std::unordered_map<int, ExplosivesDTO> explosives, std::unordered_map<int, SupplyBoxDTO> supplyBox, std::vector<uint32_t> teamsHealth);


    void send(Protocol& protocol);
    int getSerType();
    void addWorms(std::unordered_map<int, WormDTO> worms);

    std::unordered_map<int, WormDTO> getWorms();
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

    int getTimer();
    void setTimer(int timer);
    std::unordered_map<int, SupplyBoxDTO> getSupplyBox();
    
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
