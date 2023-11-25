#ifndef MATCH_COMMAND_H
#define MATCH_COMMAND_H

#include "command.h"


class Protocol;
class ConnectingUser;

class MatchCommand : public Command {
private:
    int type;
    int nrPlayers;
    std::string match;
    std::string map;
public:
    MatchCommand(int type, int nrPlayers, std::string match, std::string map);
    ~MatchCommand();
    void executeCommand(ConnectingUser& connector);
    void send(Protocol& protocol) override;
    int getID() override;
    int getType();
    int getNrPlayers();
    std::string getMatchName();
    std::string getMapName();
};




#endif