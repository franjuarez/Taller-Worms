#include "game_dynamic.h"

//martu no me mates por esta linea
GameDynamic::GameDynamic() {}


GameDynamic::GameDynamic(int wormPlayingID, std::unordered_map<int, WormDTO> worms, std::unordered_map<int, ExplosivesDTO> explosives, std::unordered_map<int, SupplyBoxDTO> supplyBox)
: Serializable() ,wormPlayingID(wormPlayingID), worms(worms), explosives(explosives), supplyBox(supplyBox), teamsHealth() {}

GameDynamic::GameDynamic(int wormPlayingID, int status, int winnerTeam, int timer, std::unordered_map<int, WormDTO> worms, std::unordered_map<int, ExplosivesDTO> explosives,
 std::unordered_map<int, SupplyBoxDTO> supplyBox, std::vector<uint32_t> teamsHealth)
: Serializable() ,wormPlayingID(wormPlayingID), winnerTeam(winnerTeam), status(status), timer(timer), worms(worms), explosives(explosives), supplyBox(supplyBox), teamsHealth(teamsHealth) {}

void GameDynamic::send(Protocol& protocol) {
    protocol.sendSerializable(this);
}

void GameDynamic::addWorms(std::unordered_map<int, WormDTO> wormVec) {
    worms = wormVec;
}

std::unordered_map<int, WormDTO> GameDynamic::getWorms() {
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

int GameDynamic::getStatus() {
    return this->status;
}

void GameDynamic::setStatus(int newStatus) {
    this->status = newStatus;
}

std::unordered_map<int, SupplyBoxDTO> GameDynamic::getSupplyBox() {
    return this->supplyBox;
}

int GameDynamic::getSerType() {
    return serializableType;
}

int GameDynamic::getTimer() {
    return this->timer;
}

void GameDynamic::setTimer(int time) {
    this->timer = time;
}

GameDynamic& GameDynamic::operator=(const GameDynamic& other) {
    if (this == &other) {
        return *this;
    }
    this->wormPlayingID = other.wormPlayingID;
    this->winnerTeam = other.winnerTeam;
    this->worms = other.worms;
    this->explosives = other.explosives;
    this->supplyBox = other.supplyBox;
    this->teamsHealth = other.teamsHealth;
    this->status = other.status;
    this->timer = other.timer;
    return *this;
}

GameDynamic::GameDynamic(const GameDynamic& other) : 
Serializable(), 
wormPlayingID(other.wormPlayingID), 
worms(other.worms) {}


GameDynamic::~GameDynamic() {}
