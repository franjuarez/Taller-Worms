#include "game_loop.h"
#include <chrono>
#include "../game_src/game_dynamic.h"
#include <unistd.h>

GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld() {}

void GameLoop::start() {

// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento
        while (true) {
                Command* command;
                while (commandsQueue.try_pop(command)) {
                        command->executeCommand(gameWorld);
                }
        std::vector<WormDTO> worms = gameWorld.update();
        GameDynamic* gameDynamic = new GameDynamic(0, worms);
        statusBroadcaster.broadcast(gameDynamic);
        usleep(33);
        // requerimos un sleep para no matar la compu wiiiii 
        }
}

GameLoop::~GameLoop() {}
