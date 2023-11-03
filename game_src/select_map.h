#ifndef SELECT_MAP_H
#define SELECT_MAP_H

#include "commands.h"

class SelectMap : public Command {

private:
    int team;
    int wormID;
    
public: 
    SelectMap(int team, int wormID);
    std::string& getMapName();
};

#endif