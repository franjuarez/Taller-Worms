#include "maps_loader.h"
#include <iostream>

#define PATH "../maps/"

MapsLoader::MapsLoader(const std::string mapsFile): file(PATH + mapsFile) {
    try{
        YAML::Node node = YAML::LoadFile(file);
        for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
            std::string mapName = it->first.as<std::string>();
            std::string mapFile = it->second.as<std::string>();
            maps[mapName] = mapFile;
        }
    } catch (const YAML::BadFile& e) {
        std::cout << "Maps YAML file not found" << std::endl;
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

Map MapsLoader::loadMap(std::string mapName) {
    if(maps.find(mapName) == maps.end()){
        throw InvalidMap("Couldn't find map with that name");
    }
    std::string mapFile = maps[mapName];
    std::string mapPath = PATH + mapFile;
    std::ifstream map(mapPath);
    if (!map) {
        throw InvalidMap("Couldn't open map file");
    }
    std::vector<WormPosition> worms;
    std::vector<BeamDTO> beams;
    std::string type;
    float coordX, coordY, angle, large;
    while (map >> type) {
        if (type == "beam") {
            map >> coordX >> coordY >> angle >> large;
            beams.push_back(BeamDTO(large, Position(coordX, coordY), angle));
        } else if (type == "worm") {
            map >> coordX >> coordY;
            worms.push_back(WormPosition{coordX, coordY});
        } else {
            throw std::invalid_argument("Invalid map file");
        }
    }
    return Map{worms, beams};
}