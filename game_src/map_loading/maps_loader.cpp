#include "maps_loader.h"
#include <iostream>

#define PATH "../maps/"
#define STARTING_WEAPONS {INFINITE_AMUNITION, INFINITE_AMUNITION, INFINITE_AMUNITION, INFINITE_AMUNITION, INFINITE_AMUNITION, INFINITE_AMUNITION, INFINITE_AMUNITION}
#define STARTING_TEAM 0

MapsLoader::MapsLoader(const std::string mapsFile): file(PATH + mapsFile) {
    try{
        YAML::Node node = YAML::LoadFile(file);
        for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
            std::string mapName = it->first.as<std::string>();
            std::string mapFile = it->second.as<std::string>();
            maps[mapName] = mapFile;
        }
    } catch (const YAML::BadFile& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Maps file not found" << std::endl;
        exit(1);
    }
}

std::vector<std::string> MapsLoader::getMapsNames() {
    std::vector<std::string> mapsNames;
    for (auto it = maps.begin(); it != maps.end(); ++it) {
        mapsNames.push_back(it->first);
    }
    return mapsNames;
}

GameMap MapsLoader::loadMap(std::string mapName) {
    if(maps.find(mapName) == maps.end()){
        throw std::invalid_argument("Map not found");
    }
    std::string mapFile = maps[mapName];
    std::string mapPath = PATH + mapFile;
    std::ifstream map(mapPath);
    if (!map) {
        throw std::invalid_argument("Map file not found");
    }
    std::vector<WormDTO> worms;
    std::vector<BeamDTO> beams;
    int idCounter = 0;
    std::string type;
    float coordX, coordY, angle, large;
    while (map >> type) {
        if (type == "beam") {
            map >> coordX >> coordY >> angle >> large;
            beams.push_back(BeamDTO(large, Position(coordX, coordY), angle));
        } else if (type == "worm") {
            map >> coordX >> coordY;
            worms.push_back(WormDTO(idCounter, 0, 0, CONFIG.getWormInitialHealth(), Position(coordX, coordY), STARTING_WEAPONS));
            idCounter++;
        } else {
            throw std::invalid_argument("Invalid map file");
        }
    }
    return GameMap(STARTING_TEAM, mapName, beams, worms);
}