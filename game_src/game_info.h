#ifndef GAME_INFO_H
#define GAME_INFO_H

#include "serializable.h"

#include <iostream>
#include <map>
#include <string>

class Protocol;

class GameInfo : public Serializable {

private:

    std::map<std::string,std::string> matchesAvailable;
    int serializableType = GAME_INFO;

public:
    GameInfo(std::map<std::string, std::string> matchesAvailable);

    void send(Protocol& protocol);
    int getSerType();

    std::map<std::string, std::string> getMatchesAvailable();

    ~GameInfo();
};

#endif
