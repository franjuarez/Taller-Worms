#include "match.h"
#include "../constants_game.h"
#include "command.h"
#include "../../shared_src/protocol.h"


MatchCommand::MatchCommand(int wormID, int type, std::string command) : Command(wormID), wormID(wormID), type(type), command(command) {}

void MatchCommand::send(Protocol& protocol) {
    protocol.sendMatchCommand(this);
}

std::string MatchCommand::executeCommand() {
    return command;
}

int MatchCommand::getID() {
    return wormID;
}

int MatchCommand::getType() {
    return type;
}

MatchCommand::~MatchCommand() {}