#ifndef MATCHES_MONITOR_H
#define MATCHES_MONITOR_H

#include "match.h"

#include <iostream>

struct InfoStruct;
struct MatchesStruct;

class MatchesMonitor {

private:
    std::mutex m;
    std::map<std::string, std::shared_ptr<MatchesStruct>> matches;

public: 
    MatchesMonitor();

    int addMatchStruct(std::string matchName, std::shared_ptr<MatchesStruct> matchStruct );

    std::map<std::string, std::string> showMatchesAvailable(); 

    int joinMatch(std::string matchName, std::shared_ptr<InfoStruct> infoStruct);

    void closeMatches();

    void startMatch(std::string matchName);

    ~MatchesMonitor();

};


#endif