
#include "commands.h"
#include "select_map.h"

SelectMap::SelectMap(int team, int wormID, std::string mapName) : Command(team, wormID), 
team(team), 
wormID(wormID), 
mapName(mapName) {}
