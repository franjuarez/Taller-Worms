#ifndef GAME_INFO_H
#define GAME_INFO_H

#include "serializable.h"

#include <iostream>
#include <vector>
#include <string>

class Protocol;

class GameInfo : public Serializable {

private:

    std::vector<std::string> mapNames;
    std::vector<std::string> matchNames;

public:
    GameInfo(std::vector<std::string> mapNames, std::vector<std::string> matchNames);

    void send(Protocol& protocol);

    std::vector<std::string> getMatchNames();
    std::vector<std::string> getMapNames();

    ~GameInfo();


};

#endif