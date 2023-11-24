#ifndef MATCH_STRUCT_H
#define MATCH_STRUCT_H

#include <vector>
#include <string>
#include <iostream>

#include "match_starter.h"
#include "constants_server.h"

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../game_src/map_loading/maps_loader.h"
#include "team.h"

#include <atomic>


struct MatchesStruct {
    std::string mapName;
    int status;
    MatchStarter* matchStarter;
    Queue<std::shared_ptr<InfoStruct>>* infoQueue;

    MatchesStruct(std::string mapName, MatchStarter* matchStarter, Queue<std::shared_ptr<InfoStruct>>* infoQueue) 
    : mapName(mapName),status(MATCH_WAITING), matchStarter(matchStarter), infoQueue(infoQueue) {}
    ~MatchesStruct() {}
};

#endif