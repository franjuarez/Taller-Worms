#include "game_info.h"
#include "../shared_src/protocol.h"

GameInfo::GameInfo(std::map<std::string, std::string> matchesAvailable) :
matchesAvailable(matchesAvailable) {}

void GameInfo::send(Protocol& protocol) {
    protocol.sendSerializable(this);
}

std::map<std::string, std::string> GameInfo::getMatchesAvailable() {
    return matchesAvailable;
}

int GameInfo::getSerType() {
    return serializableType;
}

GameInfo::~GameInfo() {}