#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "constants_server.h"

#include "../shared_src/thread.h"
#include "../game_src/map_loading/maps_loader.h"
#include "team.h"

#include <atomic>

class Player;
struct InfoStruct;
class Match;
struct MatchesStruct;
class ConnectingUser;

class Lobby : public Thread {
private:
    const std::string& hostname;
    Socket skt;
    int numberOfPlayers;
    std::string mapName;

    std::list<ConnectingUser*> connectingUsers;

    void reapDead();
    void killAll();

    std::vector<Team> createTeams(std::vector<WormDTO>& worms);

    std::vector<WormDTO> createWorms(std::vector<WormPosition> wormsPositions);

    bool* playing;
public:

    Lobby(const std::string& hostname, int numberOfPLayers, std::string mapName, bool* playing);
    void createNewMatch(std::string mapName, std::string matchName);
    // crea el new Match y lo guarda en el map dematches
    void selectMatch(std::string matchName);
    // mete al nuevo jugador en el nuevo match
    ~Lobby();
    void run() override;
};
#endif
