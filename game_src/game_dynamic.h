#ifndef GAME_DYNAMIC_H
#define GAME_DYNAMIC_H

#include "worm_dto.h"
#include "explosives_dto.h"

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
    std::vector<WormDTO> worms;
    std::unordered_map<int, ExplosivesDTO> explosives;
    std::vector<int> teamsHealth;

public: 
    //martu no me mates por esta linea 
    GameDynamic();
    GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives);
    GameDynamic(int wormPlayingID, int winnerTeam, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives, std::vector<int> teamsHealth);

    void send(Protocol& protocol);
    void addWorms(std::vector<WormDTO>worms);

    std::vector<WormDTO> getWorms();
    std::unordered_map<int, ExplosivesDTO> getExplosives();

    int getWormPlayingID();
    void setWormPlayingID(int wormPlayingID);

    int getWinnerTeam();
    void setWinnerTeam(int winnerTeam);

    void setTeamsHealth(std::vector<int> teamsHealth);
    std::vector<int> getTeamsHealth();

    int getTeamHealth(int team);
    
    GameDynamic& operator=(const GameDynamic& other);
    GameDynamic(const GameDynamic& other);
    ~GameDynamic();
};
#endif
