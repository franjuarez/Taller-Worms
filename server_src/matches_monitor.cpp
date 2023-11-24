#include "matches_monitor.h"
#include "constants_server.h"
#include "match_struct.h"


MatchesMonitor::MatchesMonitor() {}

MatchesMonitor::~MatchesMonitor() {}

void MatchesMonitor::addMatchStruct(std::string matchName, MatchesStruct* matchStruct) {
    std::lock_guard<std::mutex> lock(m);
    matches[matchName] = matchStruct;
}

std::map<std::string, std::string> MatchesMonitor::showMatchesAvailable() {
    std::map<std::string, std::string> availableMatches;
    std::lock_guard<std::mutex> lock(m);
    for (auto& match : matches) {
        if (match.second->status == MATCH_WAITING) {
            availableMatches[match.first] = match.second->mapName;
        }
    }
    return availableMatches;
}

void MatchesMonitor::changeMatchStatusToPlaying(std::string matchName) {
    std::map<std::string, std::string> availableMatches;
    matches[matchName]->status = MATCH_IN_GAME_LOOP;
}