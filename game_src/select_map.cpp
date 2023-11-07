
#include "commands.h"
#include "select_map.h"

SelectMap::SelectMap(int team, int wormID, std::string mapName) : Command(team, wormID), 
team(team), 
wormID(wormID), 
mapName(mapName) {}

std::string& SelectMap::getMapName() {
    return this->mapName;
}

void SelectMap::send(Protocol& protocol) {
    protocol.sendSelectMap(this);
}

int SelectMap::getTeam(){
    return this->team;
}

void SelectMap::executeCommand(GameWorld& gameWorld) {
    std::cout << "exec SelectMap\n";
    UNUSED(gameWorld);
}

SelectMap::~SelectMap() {}
