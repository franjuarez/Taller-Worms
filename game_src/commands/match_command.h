#ifndef MATCH_COMMAND_H
#define MATCH_COMMAND_H

#include "command.h"
#include "../constants_game.h"


class Protocol;
class ConnectingUser;

class MatchCommand : public Command {
private:
    int type;
    int nrPlayers;
    std::string match;
    std::string map;
    int commandType = COMMAND_MATCH;
public:
    MatchCommand(int type, int nrPlayers, std::string match, std::string map);
    ~MatchCommand();
    void send(Protocol& protocol) override;
    int getID() override;
    int getType();
    int getNrPlayers();
    std::string getMatchName();
    std::string getMapName();
    int getComType();
};




#endif