#ifndef SELECT_MAP_H
#define SELECT_MAP_H

#include "commands.h"

class SelectMap : public Command {

private:
    std::string& mapName;

public: 
    SelectMap(std::string&);
    std::string& getMapName();
};

#endif