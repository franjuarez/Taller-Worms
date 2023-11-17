#include "team.h"

Team::Team(int teamId) : teamId(teamId) {
    this->idPosition = 0;
}

int Team::getNextWormID(){
    this->idPosition = (this->idPosition + 1) % this->wormIDs.size();
    return this->wormIDs[this->idPosition];
}

void Team::removeWormID(int wormID){
    for (size_t i = 0; i < this->wormIDs.size(); i++){
        if (this->wormIDs[i] == wormID){
            this->wormIDs.erase(this->wormIDs.begin() + i);
            break;
        }
    }
}

bool Team::checkWormExists(int wormID) {
    for (size_t i = 0; i < this->wormIDs.size(); i++){
        if (this->wormIDs[i] == wormID){
            return true;
        }
    }
    return false;
}

void Team::addWorm(int wormID){
    wormIDs.push_back(wormID);
}

std::vector<int> Team::getWormIDs() {
    return this->wormIDs;
}

bool Team::hasWorms(){
    return this->wormIDs.size() > 0;
}

Team::~Team() {}