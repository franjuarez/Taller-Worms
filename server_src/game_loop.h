#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <vector>
#include <string>
#include <iostream>

#include "lobby.h"
#include "team.h"
#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/socket.h"
#include "../physics_src/game_world.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"
#include <unistd.h>
#include <chrono>

class GameLoop {

private: 
    Queue<Command*>& commandsQueue; // esta saca los comandos con try pop porque no la deberia bloquear y siempre tiene que estar loopeando
    StatusBroadcaster& statusBroadcaster;
    GameWorld gameWorld;
    std::vector<Team> teams;
    int teamPlayingID;
    int wormPlayingID;
    int wormPlayingHealth;
    bool waitingForStatic;
    std::chrono::steady_clock::time_point start_time; 

    void loopLogic();
    void changeWormPlaying();
public:
    GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster, GameMap* gameMap, std::vector<Team> teams);
    ~GameLoop();
    void start();
    
};
#endif