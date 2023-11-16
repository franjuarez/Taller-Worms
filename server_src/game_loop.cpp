#include "game_loop.h"
#include <chrono>
#include "../game_src/game_dynamic.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"
#include <unistd.h>
#include <chrono>

#define FPS 60.0f
#define RATE (1000.f / FPS)
#define TURN_TIME 10
#define NOONE_PLAYING -1

GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster, GameMap* gameMap, std::vector<Team> teams)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld(gameMap), teams(teams) {
	this->teamPlayingID = 0;
	this->wormPlayingID = teams[teamPlayingID].getNextWormID();
	// bool la salud del gusano jugando
	// bool -> es de herramienta
}

void GameLoop::loopLogic() {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento

	Command* command;
	while (commandsQueue.try_pop(command)) {
			command->executeCommand(gameWorld);
	}
	gameWorld.update();

	GameDynamic* gameDynamic = gameWorld.getGameStatus(wormPlayingID);
	statusBroadcaster.broadcast(gameDynamic);
	// fijar si la vida se fue al choto del gusano jugando
	std::vector<WormDTO> worms = gameDynamic->getWorms();

	for (size_t i = 0; i < worms.size(); i++) {
		int wormId = worms[i].getId();
		int wormTeam = worms[i].getTeam();
		if (!worms[i].isAlive() && teams[wormTeam].checkWormExists(wormId)) {
			teams[wormTeam].removeWormID(wormId);
		}
		// if team has worms -> you lost
	}
}

// bool waitingStable -> true -> no paso comandos

// y worm playing id -> -1

					// -> false -> paso los comandos normalmente

void GameLoop::start() {
	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	while(true) {
		loopLogic();
		usleep(RATE*1000);
		// empezar a contar el tiempo cuando waitingStable -> false
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		if (elapsed_time > TURN_TIME * 1000) {
			teamPlayingID = (teamPlayingID + 1) % teams.size();
			for(size_t i = teamPlayingID; true ; i = (i + 1) % teams.size()){
				if(teams[i].hasWorms()){
					teamPlayingID = i;
					break;
				}
			}
			wormPlayingID = teams[teamPlayingID].getNextWormID();
			// std::cout << "Changing Turn! Team: " << teamPlayingID << " Worm: " << wormPlayingID << std::endl;
			start_time = std::chrono::steady_clock::now();
		}
	}
}

GameLoop::~GameLoop() {}
