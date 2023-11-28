#ifndef MATCH_STRUCT_H
#define MATCH_STRUCT_H

#include <vector>
#include <string>
#include <iostream>

#include "match.h"
#include "constants_server.h"

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../game_src/map_loading/maps_loader.h"
#include "team.h"

#include <atomic>

struct InfoStruct;
class Match;

struct MatchesStruct {
    int status = MATCH_WAITING;
    std::string mapName;
    std::unique_ptr<Match> matchStarter;
    std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> infoQueue;

    MatchesStruct(std::vector<Team> teams, std::string matchName, 
    std::shared_ptr<GameMap> gameMap, bool* playing, std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> infoQueue) 
    : mapName(gameMap->getMapName()), matchStarter(std::make_unique<Match>(teams, infoQueue, matchName, gameMap, playing, &status)), infoQueue(infoQueue) {}
    ~MatchesStruct() {}
};

#endif