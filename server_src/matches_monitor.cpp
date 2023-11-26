#include "matches_monitor.h"
#include "constants_server.h"
#include "match_struct.h"


MatchesMonitor::MatchesMonitor() {}

MatchesMonitor::~MatchesMonitor() {
    for (auto& match : matches) {
        match.second->matchStarter->join();
    }
}

void MatchesMonitor::addMatchStruct(std::string matchName, MatchesStruct* matchStruct) {
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

void MatchesMonitor::changeMatchStatusToPlaying(std::string matchName) {
    std::map<std::string, std::string> availableMatches;
    matches[matchName]->status = MATCH_IN_GAME_LOOP;
}

void MatchesMonitor::sendInfoStruct(std::string matchName, std::shared_ptr<InfoStruct> infoStruct) {
    std::lock_guard<std::mutex> lock(m);
    Queue<std::shared_ptr<InfoStruct>>* infoQueueMatch = matches[matchName]->infoQueue;
    infoQueueMatch->push(infoStruct);
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