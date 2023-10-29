
#include "commands.h"
#include "select_map.h"

SelectMap::SelectMap(std::string& mapName) : mapName(mapName) {}

std::string& SelectMap::getMapName() {
    return this->mapName;
}