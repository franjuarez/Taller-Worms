#ifndef SELECT_MAP_H
#define SELECT_MAP_H

#include "commands.h"
#include "../shared_src/protocol.h"
class Protocol;

class SelectMap : public Command {

private:
    int team;
    int wormID;
    std::string mapName;
    
public: 
    SelectMap(int team, int wormID, std::string mapName);
    std::string& getMapName();
    void send(Protocol& protocol);
    void executeCommand() override;
    int getTeam();
    ~SelectMap();
};
#endif
