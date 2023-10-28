#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include "game_map.h"
#include "game_dynamic.h"

#include <iostream>
#include <vector>

class GameStatus {

private:
    bool newStatus = false;
    int team;
    GameMap& gameMap;
    GameDynamic& gameDynamic;

public:
    GameStatus(bool,GameMap&, GameDynamic&);
    ~GameStatus();
    // void updateMap(GameMap& gameMap);
    // void updateDynamic(GameDynamic& gameDynamic);
    bool isNewStatus();
    void updateNewStatus(bool);
    GameMap& getGameMap();
    GameStatus& operator=(const GameStatus& other); 
};
#endif
