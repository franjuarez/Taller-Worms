#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "worm.h"
#include "beam.h"

class Game {

protected:
    std::vector<std::string> mapNames = {"Aloha: devuelve lo de la clase madre",};
    int wormPlayingID = 77;
    std::vector<Worm> worms = {};
    int team = 0;
    int numberOfBeams = 0;
    std::string mapName = "";
    std::vector<Beam> beamsMap = {};
    
public: 
    Game(std::vector<std::string> mapNames, int team) : mapNames(mapNames), team(team) {}
    Game(int wormPlayingID, std::vector<Worm>worms) : wormPlayingID(wormPlayingID), worms(worms) {} 
    Game(int numberOfBeams, std::string mapName, std::vector<Beam> beamsMap) : numberOfBeams(numberOfBeams), mapName(mapName), beamsMap(beamsMap) {}
    Game() {};
    ~Game() {}

    virtual std::vector<std::string>& getMapNames() {
        return mapNames;
    }
    virtual int getTeam() {
        return team;
    }

    virtual void addWorms(std::vector<Worm> worms) {
        this->worms = worms;
    }

    virtual std::vector<Worm> getWorms() {
        return worms;
    }

    virtual int getNumberOfWorms() { 
        return worms.size();
    }
    virtual int getWormPlayingID() {
        return wormPlayingID;
    }
    virtual std::string getMapName() {
        return mapName;
    }
    virtual std::vector<Beam> getBeams(int) {
        return beamsMap;
    }
    virtual int getNumberOfBeams() {
        return numberOfBeams;
    }

    // Game& operator=(const Game& other) {
    //     if (this == &other) {
    //     return *this;
    // }
    //     this->mapName = other.mapName;
    //     this->wormPlayingID = other.wormPlayingID;
    //     this->worms = other.worms;
    //     this->mapNames = other.mapNames;
    //     this->team = other.team;
    //     this->numberOfBeams = other.numberOfBeams;
    //     this->mapName = other.mapName;
    //     this->beamsMap = other.beamsMap;
    //     return *this;
    // }

};
#endif 
