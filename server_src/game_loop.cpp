#include "game_loop.h"

#define FPS 60.0f
#define RATE (1000.f / FPS)
#define TURN_TIME 10.0f
#define NOONE_PLAYING -1


GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster, GameMap* gameMap, std::vector<Team> teams)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld(gameMap), teams(teams) {
	this->teamPlayingID = 0;
	this->wormPlayingHealth = 100;
	this->waitingForStatic = false;
	this->start_time = std::chrono::steady_clock::now();
}

void GameLoop::loopLogic(int64_t elapsed_time) {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento

	Command* command;
	while (commandsQueue.try_pop(command) && !waitingForStatic) {
			waitingForStatic = command->executeCommand(gameWorld);
	}
	gameWorld.update();

 
	GameDynamic* gameDynamic = gameWorld.getGameStatus(wormPlayingID);
	if (waitingForStatic) {
		gameDynamic->setWormPlayingID(NOONE_PLAYING);
	}
	
	std::vector<WormDTO> worms = gameDynamic->getWorms();
	int wormPlayingNewHealth;

	for (size_t i = 0; i < worms.size(); i++) {
		int wormId = worms[i].getId();

		if (wormId == wormPlayingID) {
			wormPlayingNewHealth = worms[i].getHealth();
		}

		int wormTeam = worms[i].getTeam();
		if (!worms[i].isAlive() && teams[wormTeam].checkWormExists(wormId)) {
			teams[wormTeam].removeWormID(wormId);
		}
	}

	int winningStatus = updateWinningStatus();
	gameDynamic->setWinnerTeam(winningStatus);
	statusBroadcaster.broadcast(gameDynamic);

	if (wormPlayingHealth != wormPlayingNewHealth || elapsed_time > TURN_TIME * 1000 ) {
		waitingForStatic = true;
	}

	if (waitingForStatic) {
		if(gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			changeWormPlaying(worms);
		}
	}

}

void GameLoop::start() {
	this->wormPlayingID = teams[teamPlayingID].getNextWormID();
	while(true) {
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - this->start_time).count();
		loopLogic(elapsed_time);
		usleep(RATE*1000);

	}
}

void GameLoop::changeWormPlaying(std::vector<WormDTO> worms) {
	teamPlayingID = (teamPlayingID + 1) % teams.size();

	for(size_t i = teamPlayingID; true ; i = (i + 1) % teams.size()){
		if(teams[i].hasWorms()){
			teamPlayingID = i;
			break;
		}

	}

	wormPlayingID = teams[teamPlayingID].getNextWormID();
	for (size_t i = 0; i < worms.size(); i++) {
		if (worms[i].getId() == wormPlayingID) {
			this->wormPlayingHealth = worms[i].getHealth();
			break;
		}
	}
	this->start_time = std::chrono::steady_clock::now();
	// std::cout << "Changing Turn! Team: " << teamPlayingID << " Worm: " << wormPlayingID << std::endl;
}

int GameLoop::updateWinningStatus() {
	int teamsWithWorms = 0;
	for (size_t i = 0; i < teams.size(); i++) {
		if (teams[i].hasWorms()) {
			teamsWithWorms++;
		}
	}

	if (teamsWithWorms > 1) {
		return PLAYING;
	} else if (teamsWithWorms == 1) {
		return teamPlayingID;
	}
	return ALL_LOST;
}

GameLoop::~GameLoop() {}
