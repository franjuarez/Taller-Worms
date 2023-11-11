#include "game_loop.h"
#include <chrono>
#include "../game_src/game_dynamic.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"
#include <unistd.h>

#define FPS 60.0f
#define RATE (1000.f / FPS)

GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld() {}

// static uint32 getTicks()
// {
//     static clock_t start_time = 0;
//     if (start_time == 0) {
//         start_time = clock();
//     }
// 
//     clock_t current_time = clock();
// 	std::cout << current_time << std::endl;
//     return (current_time - start_time) * 1000 / CLOCKS_PER_SEC;
// }

void GameLoop::loopLogic() {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento
	Command* command;
	while (commandsQueue.try_pop(command)) {
		// if (commad.team() == worms[wormPlayingID].team())
			command->executeCommand(gameWorld);
	}
	gameWorld.update();
	GameDynamic* gameDynamic = gameWorld.getGameStatus(0);
	statusBroadcaster.broadcast(gameDynamic);
}

void GameLoop::start() {

	// static clock_t start_time = 0;
    static clock_t start_time = clock();
    while(true) {
		loopLogic();
		usleep(RATE*1000);
		clock_t current_time =  clock();
		if ((current_time - start_time) * 1000 / CLOCKS_PER_SEC > 60) {
			std::cout << wormPlayingID<< std::endl;
			if (wormPlayingID % 2 == 0) {
				wormPlayingID = 1;
			} else {
				wormPlayingID = 2;
			}
			start_time = clock();
		}
	}
}

GameLoop::~GameLoop() {}
