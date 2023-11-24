#ifndef MATCHES_MONITOR_H
#define MATCHES_MONITOR_H

#include "match_starter.h"

#include <iostream>


struct MatchesStruct;

class MatchesMonitor {

private:
    std::mutex m;
    std::map<std::string, MatchesStruct*> matches;

public: 
    MatchesMonitor();

    void addMatchStruct(MatchesStruct* matchStruct);

};


#endif