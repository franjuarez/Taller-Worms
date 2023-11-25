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
    std::string mapName;
    int status;
    std::unique_ptr<Match> matchStarter;
    Queue<std::shared_ptr<InfoStruct>>* infoQueue;

    MatchesStruct(std::string mapName, std::unique_ptr<Match> matchStarter, Queue<std::shared_ptr<InfoStruct>>* infoQueue) 
    : mapName(mapName),status(MATCH_WAITING), matchStarter(std::move(matchStarter)), infoQueue(infoQueue) {}
    ~MatchesStruct() {}
};

#endif