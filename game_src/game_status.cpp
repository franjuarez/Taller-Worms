#include "game_status.h"
#include "../shared_src/constants.h"

GameStatus::GameStatus(bool isNew, const GameMap& gameMap, const GameDynamic& gameDynamic) 
: Game(), newStatus(isNew), gameMap(gameMap), gameDynamic(gameDynamic) {}

bool GameStatus::isNewStatus() {
    return newStatus;
}

const GameMap& GameStatus::getGameMap() {
    return gameMap;
}

GameStatus& GameStatus::operator=(const GameStatus& other) {
    if (this == &other) return *this;
    this->newStatus = other.newStatus;
    this->gameMap = other.gameMap;
    this->gameDynamic = other.gameDynamic;
    return *this;
}

GameStatus::~GameStatus() {}
