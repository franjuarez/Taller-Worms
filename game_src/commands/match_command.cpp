#include "match_command.h"
#include "../constants_game.h"
#include "command.h"


MatchCommand::MatchCommand(int type, int nrPlayers, std::string match, std::string map) 
: Command(PLAYING), type(type), nrPlayers(nrPlayers), match(match), map(map) {}

void MatchCommand::send(Protocol& protocol) {
    protocol.sendMatchCommand(this);
}

void MatchCommand::executeCommand(ConnectingUser& connector) {
    // if (this->type == NEW_MATCH) {
    //     connector.createNewMatch(nrPlayers, match, map);
    // }  else if (this->type == JOIN) {
    //     connector.joinMatch(match);
    // } else if (this->type == REFRESH) {
    //     connector.refresh();
    // }
}

int MatchCommand::getID() {
    return 0;
}

int MatchCommand::getNrPlayers() {
    return nrPlayers;
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