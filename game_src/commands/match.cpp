#include "match.h"
#include "../constants_game.h"
#include "command.h"
#include "../../shared_src/protocol.h"
#include "../../server_src/lobby.h"


MatchCommand::MatchCommand(int wormID, int type, std::string match, std::string map) 
: Command(wormID), wormID(wormID), type(type), match(match), map(map) {}

void MatchCommand::send(Protocol& protocol) {
    protocol.sendMatchCommand(this);
}

void MatchCommand::executeCommand(Lobby* lobby) {
    // lobby->algo
}

int MatchCommand::getID() {
    return wormID;
}

int MatchCommand::getType() {
    return type;
}

std::string MatchCommand::getMapName() {
    return this->map;
}

std::string MatchCommand::getMatchName() {
    return this->match;
}

MatchCommand::~MatchCommand() {}