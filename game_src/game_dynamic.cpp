#include "game_dynamic.h"

//martu no me mates por esta linea
GameDynamic::GameDynamic() {}


GameDynamic::GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives)
: Serializable() ,wormPlayingID(wormPlayingID), worms(worms), explosives(explosives), teamsHealth() {}

GameDynamic::GameDynamic(int wormPlayingID, int winnerTeam, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives, std::vector<uint32_t> teamsHealth)
: Serializable() ,wormPlayingID(wormPlayingID), winnerTeam(winnerTeam), worms(worms), explosives(explosives), teamsHealth(teamsHealth) {}

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

void GameDynamic::setTeamsHealth(std::vector<uint32_t> teamsHealth) {
    this->teamsHealth = teamsHealth;
}

std::vector<uint32_t> GameDynamic::getTeamsHealth() {
    return this->teamsHealth;
}

uint32_t GameDynamic::getTeamHealth(int team) {
    return this->teamsHealth.at(team);
}

GameDynamic& GameDynamic::operator=(const GameDynamic& other) {
    if (this == &other) {
        return *this;
    }
    this->wormPlayingID = other.wormPlayingID;
    this->winnerTeam = other.winnerTeam;
    this->worms = other.worms;
    this->explosives = other.explosives;
    this->teamsHealth = other.teamsHealth;
    return *this;
}

GameDynamic::GameDynamic(const GameDynamic& other) : 
Serializable(), 
wormPlayingID(other.wormPlayingID), 
worms(other.worms) {}


GameDynamic::~GameDynamic() {}
