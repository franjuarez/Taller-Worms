#ifndef COMMANDS_MATCH_H
#define COMMANDS_MATCH_H

#include "command.h"

class Protocol;
class Lobby;

class MatchCommand : public Command {
private:
    int wormID;
    int type;
    std::string match;
    std::string map;
public:
    MatchCommand(int wormID, int type, std::string match, std::string map);
    ~MatchCommand();
    void executeCommand(Lobby* lobby);
    void send(Protocol& protocol) override;
    int getID() override;
    int getType();
    std::string getMatchName();
    std::string getMapName();
};




#endif