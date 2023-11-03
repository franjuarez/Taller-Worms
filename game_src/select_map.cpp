
#include "commands.h"
#include "select_map.h"

SelectMap::SelectMap(int team, int wormID) : Command(team, wormID), 
team(team), 
wormID(wormID) {}
