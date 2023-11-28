#include "game_info.h"
#include "../shared_src/protocol.h"

GameInfo::GameInfo(std::map<std::string, std::string> matchesAvailable) :
matchesAvailable(matchesAvailable) {}

void GameInfo::send(Protocol& protocol) {
    protocol.sendInfo(this);
}

std::map<std::string, std::string> GameInfo::getMatchesAvailable() {
    return matchesAvailable;
}

GameInfo::~GameInfo() {}