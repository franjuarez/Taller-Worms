#include "matches_monitor.h"
#include "constants_server.h"
#include "match_struct.h"
#include "../shared_src/info_struct.h"

MatchesMonitor::MatchesMonitor() {}

MatchesMonitor::~MatchesMonitor() {
    for (auto& match : matches) {
        match.second->matchStarter->join();
    }
}

void MatchesMonitor::addMatchStruct(std::string matchName, std::shared_ptr<MatchesStruct> matchStruct ) {
    std::lock_guard<std::mutex> lock(m);
    matches[matchName] = matchStruct;
    matchStruct->matchStarter->start();
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


int MatchesMonitor::joinMatch(std::string matchName, std::shared_ptr<InfoStruct> infoStruct) {
    std::lock_guard<std::mutex> lock(m);
    if (matches[matchName]->status == MATCH_IN_GAME_LOOP) {
        return ERROR;
    }

    std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> infoQueueMatch = matches[matchName]->infoQueue;
    infoQueueMatch->push(infoStruct);
    return OK;
}

void MatchesMonitor::closeMatches() {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Cerrando matches" << std::endl;
    for (auto& match : matches) {
        match.second->infoQueue->close();
        match.second->matchStarter->join();
    }
    matches.clear();
    std::cout << "Matches cerrados" << std::endl;
}

bool MatchesMonitor::nameDoesntExists(std::string matchName) {
    auto name = matches.find(matchName);
    return name == matches.end();
}