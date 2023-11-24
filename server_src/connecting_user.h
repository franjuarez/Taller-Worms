#ifndef CONNECTING_USER_H
#define CONNECTING_USER_H

#include "../shared_src/thread.h"
#include "match_starter.h"
#include "match_struct.h"
#include "matches_monitor.h"
#include "constants_server.h"

struct InfoStruct;


class ConnectingUser : public Thread {

private:
    int status;
    std::shared_ptr<InfoStruct> infoStruct;
    MatchesMonitor& matchesMonitor;

    std::vector<Team> createTeams(std::vector<WormDTO>& worms, int numberOfPlayers);
    std::vector<WormDTO> createWorms(std::vector<WormPosition> wormsPositions);

public:
    ConnectingUser(std::shared_ptr<InfoStruct> infoStruct, MatchesMonitor& matchesMonitor);
    void run() override;
    bool isActive();
    ~ConnectingUser();
};
#endif
