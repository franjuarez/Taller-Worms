#ifndef COMMANDS_MATCH_H
#define COMMANDS_MATCH_H

#include "command.h"

class Protocol;

class MatchCommand : public Command {
private:
    int wormID;
    int type;
    std::string command;
public:
    MatchCommand(int wormID, int type, std::string command);
    ~MatchCommand();
    std::string executeCommand();
    void send(Protocol& protocol) override;
    int getID() override;
    int getType();
};




#endif