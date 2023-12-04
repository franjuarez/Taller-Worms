#ifndef CONNECTING_USER_H
#define CONNECTING_USER_H

#include "../shared_src/thread.h"
#include "../shared_src/info_struct.h"
#include "match.h"
#include "match_struct.h"
#include "matches_monitor.h"
#include "constants_server.h"

struct InfoStruct;
class MatchesMonitor;

class ConnectingUser : public Thread {

private:
    int status;
    std::shared_ptr<InfoStruct> infoStruct;
    MatchesMonitor& matchesMonitor;
    bool* playing;
    std::vector<Team> createTeams(std::vector<WormDTO>& worms, int numberOfPlayers);
    std::vector<WormDTO> createWorms(std::vector<WormPosition> wormsPositions);
    std::unordered_map<int, WormDTO> makeWormsMap(std::vector<WormDTO>& worms);
public:
    ConnectingUser(std::shared_ptr<InfoStruct> infoStruct, MatchesMonitor& matchesMonitor, bool* playing);
    void run() override;

    void createNewMatch(int numberOfPlayers, std::string matchName, std::string mapName);
    void joinMatch(std::string matchName);
    void refresh();

    bool isActive();

    void kill();
    ~ConnectingUser();
};
#endif
