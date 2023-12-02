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

int MatchesMonitor::addMatchStruct(std::string matchName, std::shared_ptr<MatchesStruct> matchStruct ) {
    std::lock_guard<std::mutex> lock(m);
    reapMatches();
    auto name = matches.find(matchName);
    if (name != matches.end()) {
        return ERROR;
    }
    matches[matchName] = matchStruct;
    return OK;
}

void MatchesMonitor::startMatch(std::string matchName) {
    matches[matchName]->matchStarter->start();
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
    // std::cout << "Cerrando matches" << std::endl;
    for (auto& match : matches) {
        match.second->infoQueue->close();
        match.second->matchStarter->join();
    }
    matches.clear();
    // std::cout << "Matches cerrados" << std::endl;
}


void MatchesMonitor::reapMatches() {
    // std::lock_guard<std::mutex> lock(m);
    std::vector<std::string> matchesToDelete = {};
    for (auto& match : matches) {
        if (match.second->status == MATCH_OVER) {
            match.second->infoQueue->close();
            match.second->matchStarter->join();
            matchesToDelete.push_back(match.first);
        }
    }
    for (long unsigned int i = 0; i < matchesToDelete.size(); i++) {
        matches.erase(matchesToDelete[i]);
    }
}