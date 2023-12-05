#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "constants_server.h"

#include "../shared_src/thread.h"
#include "../shared_src/socket.h"
#include "../shared_src/liberror.h"
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

    bool* playing;
public:

    Lobby(const std::string& hostname, int numberOfPLayers, std::string mapName, bool* playing);
    ~Lobby();
    void run() override;
    void stop();
};
#endif
