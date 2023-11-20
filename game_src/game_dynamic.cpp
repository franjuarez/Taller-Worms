#include "game_dynamic.h"

GameDynamic::GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives)
: Serializable() ,wormPlayingID(wormPlayingID), winnerTeam(PLAYING), worms(worms), explosives(explosives) {}

GameDynamic::GameDynamic(int wormPlayingID, int winnerTeam, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives)
: Serializable() ,wormPlayingID(wormPlayingID), winnerTeam(winnerTeam), worms(worms), explosives(explosives) {}

void GameDynamic::send(Protocol& protocol) {
    protocol.sendDynamic(this);
}

void GameDynamic::addWorms(std::vector<WormDTO> wormVec) {
    worms = wormVec;
}

std::vector<WormDTO> GameDynamic::getWorms() {
    return this->worms;
}

std::unordered_map<int, ExplosivesDTO> GameDynamic::getExplosives() {
    return this->explosives;
}

int GameDynamic::getWormPlayingID() {
    return this->wormPlayingID;
}

void GameDynamic::setWormPlayingID(int wormPlayingID) {
    this->wormPlayingID = wormPlayingID;
}

int GameDynamic::getWinnerTeam() {
    return this->winnerTeam;
}

void GameDynamic::setWinnerTeam(int winnerTeam) {
    this->winnerTeam = winnerTeam;
}

GameDynamic& GameDynamic::operator=(const GameDynamic& other) {
    if (this == &other) {
        return *this;
    }
    this->wormPlayingID = other.wormPlayingID;
    this->winnerTeam = other.winnerTeam;
    this->worms = other.worms;
    this->explosives.clear();
    this->explosives.insert(other.explosives.begin(), other.explosives.end());
    return *this;
}

GameDynamic::GameDynamic(const GameDynamic& other) : 
Serializable(), 
wormPlayingID(other.wormPlayingID), 
worms(other.worms) {}


GameDynamic::~GameDynamic() {}
