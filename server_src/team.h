#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <vector>
#include <map>

class Team {

private:

    int teamId;
    int idPosition;
    std::vector<int> wormIDs;

public:    
    explicit Team(int teamId);

    int getNextWormID();

    void removeWormID(int wormID);

    bool checkWormExists(int wormID);

    void addWorm(int wormID);

    std::vector<int> getWormIDs();

    bool hasWorms();

    ~Team();

};
#endif
