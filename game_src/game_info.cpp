#include "game_info.h"
#include "../shared_src/protocol.h"

GameInfo::GameInfo(std::vector<std::string> mapNames, std::vector<std::string> matchNames) :
mapNames(mapNames), matchNames(matchNames) {}

void GameInfo::send(Protocol& protocol) {
    protocol.sendInfo(this);
}

std::vector<std::string> GameInfo::getMapNames() {
    return mapNames;
}

std::vector<std::string> GameInfo::getMatchNames() {
    return matchNames;
}


GameInfo::~GameInfo() {}