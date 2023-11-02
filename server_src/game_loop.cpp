#include "game_loop.h"

GameLoop::GameLoop(Queue<Command>& commandsQueue, StatusBroadcaster& statusBroadcaster) 
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster) {}

void GameLoop::start() {
        std::vector<Worm> worms;
        Position pos(1.0, 1.4);
        worms.push_back(Worm(0, 79, 1, pos));
        Position pos2(9.89, 12.1);
        worms.push_back(Worm(8, 9, 1, pos2));
        GameDynamic gameDynamic(0, worms);
        statusBroadcaster.broadcast(gameDynamic);

        std::vector<Worm> worms2;
        Position pos3(1.5, 1.7);
        worms2.push_back(Worm(0, 35, 1, pos3));
        Position pos4(9.33, 1.1);
        worms2.push_back(Worm(8, 2, 1, pos4));
        GameDynamic gameDynamic2(0, worms2);
        statusBroadcaster.broadcast(gameDynamic2);
}

GameLoop::~GameLoop() {}