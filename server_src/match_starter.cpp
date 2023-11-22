#include "match_starter.h"

MatchStarter::MatchStarter(Queue<std::string>& matchNamesQueue, Queue<std::shared_ptr<Player>>& playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap) : 
matchNamesQueue(matchNamesQueue), playerInfoQueue(playerInfoQueue), matchName(matchName), gameMap(gameMap) {
    numberOfPlayers = gameMap->getNumberTeams();
}


void MatchStarter::run() {}


MatchStarter::~MatchStarter() {}