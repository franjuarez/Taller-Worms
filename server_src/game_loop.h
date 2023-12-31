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
#include <atomic>
#include <random>

class StatusBroadcaster;

class GameLoop{

private: 
    Queue<std::shared_ptr<Command>>& commandsQueue; 
    StatusBroadcaster& statusBroadcaster;
    GameWorld gameWorld;
    std::vector<Team> teams;
    int teamPlayingID;
    int wormPlayingID;
    int wormPlayingHealth;
    bool waitingForStatic = false;
    bool waitingExtraTime = false;
    std::chrono::steady_clock::time_point start_time; 
    std::chrono::steady_clock::time_point start_extra_time;
    bool cheatOn = false;
    int waitingForBox = 0;
    bool stillWaiting = false;
    bool* playing;
    bool gameOver = false;
    bool playingDone = false;

    void loopLogic(int64_t passed_time);
    int updateWinningStatus();
    void changeWormPlaying(std::unordered_map<int, WormDTO> worms);
    bool shouldDropBox();
    int decideTypeOfSupplyBox();
    int decideAmmoType();
    int dropSupplyBox();
    void reset();
    void checkPlayers();
    int updateGameDynamic(std::shared_ptr<GameDynamic> gameDynamic, std::unordered_map<int, WormDTO> worms, int64_t elapsed_time);

public:
    GameLoop(Queue<std::shared_ptr<Command>>& commandsQueue, StatusBroadcaster& statusBroadcaster, std::shared_ptr<GameMap> gameMap, std::vector<Team> teams, bool* playing);
    ~GameLoop();
    void run();
};
#endif