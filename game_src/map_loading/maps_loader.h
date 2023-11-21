#ifndef MAPS_LOADER_H
#define MAPS_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include "../game_map.h"
#include "../../shared_src/constants.h"
#include "invalid_map_error.h"

struct WormPosition {
    float x;
    float y;
};

struct Map{
    std::vector<WormPosition> worms;
    std::vector<BeamDTO> beams;
};

class MapsLoader {
private:
    const std::string file;
    std::unordered_map<std::string, std::string> maps;

public:
    // Constructor
    explicit MapsLoader(const std::string mapsFile);

    std::vector<std::string> getMapsNames();

    Map loadMap(std::string mapName);
};

#endif
